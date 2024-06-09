#include "../include/exec.h"

int	execute_command_internal(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->u_value.simple,
				pipe_in, pipe_out, last_command_exit_status));
	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		return (execute_connection(command, pipe_in, pipe_out,
				last_command_exit_status));
}

int	execute_command(t_command *command, int last_command_exit_status)
{
	pid_t	last_made_pid;
	int		status;
	int		waitpid_result;

	last_made_pid = execute_command_internal(command, NO_PIPE, NO_PIPE,
			last_command_exit_status);
	if (last_made_pid == EXECUTION_FAILURE
		|| last_made_pid == EXECUTION_SUCCESS)
		return (last_made_pid);
	waitpid_result = waitpid(last_made_pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (waitpid_result == -1) // when waitpid failed (waitpid return -1), already done waitpid (in andlist or orlist function)
		return (last_made_pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // forbidden function ??
	else // (WIFSIGNALED(status))
		return (128 + WTERMSIG(status)); // forbidden function ??
}
