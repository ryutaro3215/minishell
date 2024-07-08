/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_connection_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:05 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:57:39 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/exec_bonus.h"

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	fildes[2];

	if (pipe(fildes) < 0)
	{
		write(2, "minishell: pipe error\n", 23);
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
			pipe_in, NO_PIPE, last_command_exit_status);
	if (last_made_pid == EXECUTION_FAILURE)
		return (last_made_pid);
	if (last_made_pid == EXECUTION_SUCCESS)
		return (execute_command_internal(command->u_value.connection->second,
				NO_PIPE, pipe_out, last_command_exit_status));
	handle_error(waitpid(last_made_pid, &status, 0) == -1);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0)
			return (WEXITSTATUS(status));
		return (execute_command_internal(command->u_value.connection->second,
				NO_PIPE, pipe_out, last_command_exit_status));
	}
	else
		return (128 + WTERMSIG(status));
}

int	execute_orlist(t_command *command, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	int	last_made_pid;
	int	status;

	last_made_pid = execute_command_internal(command->u_value.connection->first,
			pipe_in, NO_PIPE, last_command_exit_status);
	if (last_made_pid == EXECUTION_SUCCESS)
		return (last_made_pid);
	if (last_made_pid == EXECUTION_FAILURE)
		return (execute_command_internal(command->u_value.connection->second,
				NO_PIPE, pipe_out, last_command_exit_status));
	handle_error(waitpid(last_made_pid, &status, 0) == -1);
	while (wait(NULL) != -1)
		continue ;
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 0)
			return (WEXITSTATUS(status));
		return (execute_command_internal(command->u_value.connection->second,
				NO_PIPE, pipe_out, last_command_exit_status));
	}
	else
		return (128 + WTERMSIG(status));
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
		return (execute_andlist(command, pipe_in, pipe_out,
				last_command_exit_status));
	else
		return (execute_orlist(command, pipe_in, pipe_out,
				last_command_exit_status));
}
