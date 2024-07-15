/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:40:52 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/07/15 10:48:25 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/signal.h"

volatile sig_atomic_t	g_interrupt_state = 0;

void	sigint_handler_for_readline(int sig)
{
	(void)sig;
	g_interrupt_state = 1;
}

void	sigint_handler_for_exec(int sig)
{
	(void)sig;
	write(1, "\n", 2);
}

int	sigint_is_traped(int last_command_exit_status)
{
	if (g_interrupt_state)
	{
		g_interrupt_state = 0;
		return (128 + SIGINT);
	}
	return (last_command_exit_status);
}

int	event_hook_for_readline(void)
{
	if (g_interrupt_state)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
