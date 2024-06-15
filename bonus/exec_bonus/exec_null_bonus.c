/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_null_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:12 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:52:13 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/exec_bonus.h"

int	execute_null_command(t_redirect *redirect_list, int pipe_in, int pipe_out)
{
	pid_t	pid;

	pid = do_fork();
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
