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
		ft_err_printf("fork error\n");
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
			ft_err_printf("dup error\n");
			return (fd);
		}
		close(pipe_in);
	}
	if (pipe_out != NO_PIPE)
	{
		fd = dup2(pipe_out, 1);
		if (fd < 0)
		{
			ft_err_printf("dup error\n");
			return (fd);
		}
		close(pipe_out);
	}
	return (fd);
}
