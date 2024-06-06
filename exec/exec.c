#include "../include/exec.h"

int	execute_builtin(t_simple *simple, int (*builtin)(t_token *))
{
	char	*underscore;
	char	*environ_var;
	int		fdin_tmp;
	int		fdout_tmp;
	int		exit_status;

	// update underscore environ.
	underscore = strdup("_=");
	environ_var = strjoin_but_freed_only_first_arg(underscore, simple->word_list->name);
	replace_environ_var(environ_var);
	free(environ_var);

	fdin_tmp = dup(STDIN_FILENO);
	fdout_tmp = dup(STDOUT_FILENO);
	if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	exit_status = builtin(simple->word_list);
	dup2(fdin_tmp, 0);
	dup2(fdout_tmp, 1);
	close(fdin_tmp);
	close(fdout_tmp);
	return (exit_status);
}

int	execute_disk_command(char *path, char **argv)
{
	extern char	**environ;
	char		*underscore;
	char		*environ_var;

	// update underscore environ.
	underscore = strdup("_=");
	environ_var = strjoin_but_freed_only_first_arg(underscore, path);
	replace_environ_var(environ_var);
	free(environ_var);
	execve(path, argv, environ);
	printf("minishell: command not found: %s\n", argv[0]);
	return (COMMAND_NOT_FOUND);
}

int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out, int (*builtin)(t_token *))
{
	pid_t	pid;
	char	*path;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (pipe_in != NO_PIPE)
		{
			dup2(pipe_in, 0); // need error check
			close(pipe_in); // need error check
		}
		if (pipe_out != NO_PIPE)
		{
			dup2(pipe_out, 1);
			close(pipe_out);
		}
		path = get_path(simple->word_list->name);
		argv = get_argv(simple->word_list);
		if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
			exit(EXECUTION_FAILURE);
		if (builtin)
			exit(execute_builtin(simple, builtin));
		exit(execute_disk_command(path, argv));
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	// isatty() ?? reset redirect ??
	return (pid);
}

int	execute_null_command()
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return EXECUTION_FAILURE;
	if (pid == 0)
		exit(EXECUTION_SUCCESS);
	return (pid);
}

int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out, int last_command_exit_status)
{
	int (*builtin)(t_token *);

	expand_words(simple, last_command_exit_status);
	// if word_list is null, or $foo command does not exist.
	if (!simple->word_list)
			return (execute_null_command());
	builtin = find_shell_builtin(simple->word_list->name);
	if (builtin && (pipe_in == NO_PIPE && pipe_out == NO_PIPE))
		return (execute_builtin(simple, builtin));
	return (execute_in_subshell(simple, pipe_in, pipe_out, builtin));
}

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status)
{
	int	fildes[2];

	if (pipe(fildes) < 0)
	{
		printf("internal error: pipe\n");
		return (EXECUTION_FAILURE);
	}
	execute_command_internal(command->value.connection->first, pipe_in, fildes[1], last_command_exit_status);
	return (execute_command_internal(command->value.connection->second, fildes[0], pipe_out, last_command_exit_status));
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status)
{
//	int	connector = command->value.connection->connector;

	// if (connector == pipe)
	return (execute_pipeline(command, pipe_in, pipe_out, last_command_exit_status));
	// else if (connector == ...) you can add '&&' '||' '&'
}

int	execute_command_internal(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->value.simple, pipe_in, pipe_out, last_command_exit_status));
	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		return (execute_connection(command, pipe_in, pipe_out, last_command_exit_status));
}

int	execute_command(t_command *command, int last_command_exit_status)
{
	pid_t	last_made_pid;
	int		status;

	last_made_pid = execute_command_internal(command, NO_PIPE, NO_PIPE, last_command_exit_status);
	if (last_made_pid == EXECUTION_FAILURE || last_made_pid == EXECUTION_SUCCESS)
		return (last_made_pid);
	waitpid(last_made_pid, &status, 0); // need error check.
	while (wait(NULL) != -1)
		continue;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // forbidden function ??
	else // (WIFSIGNALED(status))
		return (128 + WTERMSIG(status)); // forbidden function ??
}
