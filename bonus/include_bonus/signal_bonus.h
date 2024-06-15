/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:27 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:28 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_BONUS_H
# define SIGNAL_BONUS_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

void	sigint_handler_for_readline(int sig);
void	sigint_handler_for_exec(int sig);
int		sigint_is_traped(int last_command_exit_status);
bool	sigint_is_traped_for_heredoc(void);
int		event_hook_for_readline(void);

#endif
