/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_fork_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:02 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:03 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

pid_t	do_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		write(2, "fork error\n", 12);
	return (pid);
}

int	do_pipe(int pipe_in, int pipe_out)
{
	int	fd;

	fd = 0;
	if (pipe_in != NO_PIPE)
	{
		fd = dup2(pipe_in, 0);
		if (fd < 0)
		{
			write(2, "dup error\n", 11);
			return (fd);
		}
		close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		fd = dup2(pipe_out, 1);
		if (fd < 0)
		{
			write(2, "dup error\n", 11);
			return (fd);
		}
		close(pipe_out);
	}
	return (fd);
}
