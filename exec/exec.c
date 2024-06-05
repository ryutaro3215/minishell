#include "../include/exec.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	return (s3);
}

int	execute_builtin(t_token *word_list, int (*builtin)(t_token *))
{
	char	*underscore;
	char	*environ_var;

	underscore = strdup("_=");
	environ_var = ft_strjoin(underscore, word_list->name);
	replace_environ_var(environ_var);
	free(underscore);
	free(environ_var);
	return (builtin(word_list));
}

int	execute_disk_command(char *path, char **argv)
{
	extern char	**environ;
	char		*underscore;
	char		*environ_var;

	underscore = strdup("_=");
	environ_var = ft_strjoin(underscore, path);
	replace_environ_var(environ_var);
	free(underscore);
	free(environ_var);
	builtin_env(NULL);
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
		// should handle "if NULL" ? (but error message)
		argv = get_argv(simple->word_list);
		if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
			exit(EXECUTION_FAILURE);
		if (builtin)
			exit(execute_builtin(simple->word_list, builtin));
		exit(execute_disk_command(path, argv));
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	// isatty() ?? reset redirect ??
	return (pid);
}

int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out)
{
	int (*builtin)(t_token *) = find_shell_builtin(simple->word_list->name);

	if (builtin && (pipe_in == NO_PIPE && pipe_out == NO_PIPE))
		return (execute_builtin(simple->word_list, builtin));
	return (execute_in_subshell(simple, pipe_in, pipe_out, builtin));
}

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out)
{
	int	fildes[2];

	if (pipe(fildes) < 0)
	{
		printf("internal error: pipe\n");
		return (EXECUTION_FAILURE);
	}
	execute_command_internal(command->value.connection->first, pipe_in, fildes[1]);
	return (execute_command_internal(command->value.connection->second, fildes[0], pipe_out));
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out)
{
//	int	connector = command->value.connection->connector;

	// if (connector == pipe)
	return (execute_pipeline(command, pipe_in, pipe_out));
	// else if (connector == ...) you can add '&&' '||' '&'
}

int	execute_command_internal(t_command *command, int pipe_in, int pipe_out)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->value.simple, pipe_in, pipe_out));
	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		return (execute_connection(command, pipe_in, pipe_out));
}

int	execute_command(t_command *command)
{
	pid_t	last_made_pid;
	int		status;

	last_made_pid = execute_command_internal(command, NO_PIPE, NO_PIPE);
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
