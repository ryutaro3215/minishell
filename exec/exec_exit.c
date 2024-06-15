/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:08 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:09 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	execute_exit_builtin(t_simple *simple, int last_command_exit_status)
{
	char	*underscore;
	char	*environ_var;

	// update underscore environ.
	underscore = ft_strdup("_=");
	environ_var = strjoin_but_freed_only_first_arg(underscore,
			simple->word_list->name);
	replace_environ_var(environ_var);
	free(environ_var);
	if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
		return (EXECUTION_FAILURE);
	builtin_exit(simple->word_list, last_command_exit_status);
	return (EXECUTION_FAILURE);
}

int	execute_exit_in_subshell(t_simple *simple, int pipe_in, int pipe_out,
	int last_command_exit_status)
{
	pid_t	pid;

	pid = do_fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (do_pipe(pipe_in, pipe_out) < 0)
			exit(EXECUTION_FAILURE);
		if (do_redirect(simple->redirect_list) == EXECUTION_FAILURE)
			exit(EXECUTION_FAILURE);
		builtin_exit(simple->word_list, last_command_exit_status);
		return (EXECUTION_FAILURE);
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	return (pid);
}
