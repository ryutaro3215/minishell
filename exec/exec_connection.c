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

int	execute_connection(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
//	int	connector = command->value.connection->connector;
	// if (connector == pipe)
	return (execute_pipeline(command, pipe_in, pipe_out,
			last_command_exit_status));
	// else if (connector == ...) you can add '&&' '||' '&'
}
