#include "../include/exec.h"

int	execute_exit_builtin(t_simple *simple, int last_command_exit_status)
{
	char	*underscore;
	char	*environ_var;

	// update underscore environ.
	underscore = ft_strdup("_=");
	environ_var = strjoin_but_freed_only_first_arg(underscore,
			simple->word_list->name);
	replace_environ_var(environ_var);
	free(environ_var);
	if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	builtin_exit(last_command_exit_status);
	return (EXECUTION_SUCCESS);
}

int	execute_exit_in_subshell(t_simple *simple, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	pid_t	pid;

	pid = do_fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (do_pipe(pipe_in, pipe_out) < 0)
			exit(EXECUTION_FAILURE);
		if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
			exit(EXECUTION_FAILURE);
		builtin_exit(last_command_exit_status);
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	return (pid);
}
