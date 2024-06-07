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
	environ_var
		= strjoin_but_freed_only_first_arg(underscore, simple->word_list->name);
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

int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out,
	int (*builtin)(t_token *))
{
	pid_t	pid;
	char	*path;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (do_pipe(pipe_in, pipe_out) < 0)
			exit(EXECUTION_FAILURE);
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

int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	(*builtin)(t_token *);

	expand_words(simple, last_command_exit_status);
	// if word_list is null, or $foo command does not exist.
	if (!simple->word_list)
		return (execute_null_command(simple->redirect_list, pipe_in, pipe_out));
	builtin = find_shell_builtin(simple->word_list->name);
	if (builtin && (pipe_in == NO_PIPE && pipe_out == NO_PIPE))
	{
		if (strcmp(simple->word_list->name, "exit") == 0)
			return (execute_exit_builtin(simple, last_command_exit_status));
		return (execute_builtin(simple, builtin));
	}
	if (strcmp(simple->word_list->name, "exit") == 0)
		return (execute_exit_in_subshell(simple, pipe_in, pipe_out,
				last_command_exit_status));
	return (execute_in_subshell(simple, pipe_in, pipe_out, builtin));
}
