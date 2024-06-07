#include "../include/exec.h"

int	execute_null_command(t_redirect *redirect_list, int pipe_in, int pipe_out)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (do_pipe(pipe_in, pipe_out) < 0)
			exit(EXECUTION_FAILURE);
		if (do_redirect(redirect_list) == EXECUTION_FAILURE)
			exit(EXECUTION_FAILURE);
		exit(EXECUTION_SUCCESS);
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	return (pid);
}
