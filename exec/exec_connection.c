#include "../include/exec.h"

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	fildes[2];

	if (pipe(fildes) < 0)
	{
		ft_err_printf("minishell: pipe error\n");
		return (EXECUTION_FAILURE);
	}
	execute_command_internal(command->u_value.connection->first,
		pipe_in, fildes[1], last_command_exit_status);
	return (execute_command_internal(command->u_value.connection->second,
			fildes[0], pipe_out, last_command_exit_status));
}

int	execute_andlist(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	last_made_pid;
	int	status;

	last_made_pid = execute_command_internal(command->u_value.connection->first,
			pipe_in, pipe_out, last_command_exit_status);
	if (last_made_pid == EXECUTION_FAILURE)
		return (last_made_pid);
	if (last_made_pid == EXECUTION_SUCCESS)
		return (execute_command_internal(command->u_value.connection->second,
				pipe_in, pipe_out, last_command_exit_status));
	handle_error(waitpid(last_made_pid, &status, 0) == -1);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
		return (execute_command_internal(command->u_value.connection->second,
				pipe_in, pipe_out, last_command_exit_status));
	}
	else // (WIFSIGNALED(status))
		return (128 + WTERMSIG(status)); // forbidden function ??
}

int	execute_orlist(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	last_made_pid;
	int	status;

	last_made_pid = execute_command_internal(command->u_value.connection->first,
			NO_PIPE, NO_PIPE, last_command_exit_status);
	if (last_made_pid == EXECUTION_SUCCESS)
		return (last_made_pid);
	if (last_made_pid == EXECUTION_FAILURE)
		return (execute_command_internal(command->u_value.connection->second,
				pipe_in, pipe_out, last_command_exit_status));
	handle_error(waitpid(last_made_pid, &status, 0) == -1);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (WEXITSTATUS(status));
		return (execute_command_internal(command->u_value.connection->second,
				pipe_in, pipe_out, last_command_exit_status));
	}
	else // (WIFSIGNALED(status))
		return (128 + WTERMSIG(status)); // forbidden function ??
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	connector;

	connector = command->u_value.connection->connector;
	if (connector == pipeline)
		return (execute_pipeline(command, pipe_in, pipe_out,
				last_command_exit_status));
	else if (connector == andlist)
		return (execute_andlist(command, NO_PIPE, NO_PIPE,
				last_command_exit_status));
	else // (connector == orlist)
		return (execute_orlist(command, NO_PIPE, NO_PIPE,
				last_command_exit_status));
}
