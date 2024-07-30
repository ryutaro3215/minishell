/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:18 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:19 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	execute_command_internal(t_command *command, int *pipe_in_out,
	int last_command_exit_status, int close_fd)
{
	if (command->attribute == cm_simple)
		return (execute_simple_command(command->u_value.simple,
				pipe_in_out, last_command_exit_status, close_fd));
	else
		return (execute_connection(command, pipe_in_out[0], pipe_in_out[1],
				last_command_exit_status));
}

int	execute_command(t_command *command, int last_command_exit_status)
{
	pid_t	last_made_pid;
	int		status;
	int		waitpid_result;
	int		pipe_in_out[2];

	pipe_in_out[0] = NO_PIPE;
	pipe_in_out[1] = NO_PIPE;
	last_made_pid = execute_command_internal(command, pipe_in_out,
			last_command_exit_status, NO_PIPE);
	if (last_made_pid == EXECUTION_FAILURE
		|| last_made_pid == EXECUTION_SUCCESS)
		return (last_made_pid);
	waitpid_result = waitpid(last_made_pid, &status, 0);
	while (wait(NULL) != -1)
		continue ;
	if (waitpid_result == -1)
		return (last_made_pid);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (128 + WTERMSIG(status));
}
