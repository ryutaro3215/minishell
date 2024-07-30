/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_connection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:05 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:06 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	fildes[2];
	int	first_pipe_in_out[2];
	int	second_pipe_in_out[2];

	if (pipe(fildes) < 0)
	{
		write(2, "minishell: pipe error\n", 23);
		return (EXECUTION_FAILURE);
	}
	first_pipe_in_out[0] = pipe_in;
	first_pipe_in_out[1] = fildes[1];
	second_pipe_in_out[0] = fildes[0];
	second_pipe_in_out[1] = pipe_out;
	execute_command_internal(command->u_value.connection->first,
		first_pipe_in_out, last_command_exit_status, fildes[0]);
	return (execute_command_internal(command->u_value.connection->second,
			second_pipe_in_out, last_command_exit_status, fildes[1]));
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	connector;

	connector = command->u_value.connection->connector;
	if (connector == pipeline)
		return (execute_pipeline(command, pipe_in, pipe_out,
				last_command_exit_status));
	else
		return (EXECUTION_SUCCESS);
}
