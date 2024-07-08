/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:50:53 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:50:55 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/builtin_bonus.h"

int	retrieve_fdin_fdout(int fdin, int fdout)
{
	if (dup2(fdin, 0) < 0 || dup2(fdout, 1) < 0)
	{
		close(fdin);
		close(fdout);
		write(2, "dup error\n", 11);
		return (-1);
	}
	return (0);
}

void	*find_shell_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (&builtin_echo);
	else if (ft_strcmp(command, "cd") == 0)
		return (&builtin_cd);
	else if (ft_strcmp(command, "pwd") == 0)
		return (&builtin_pwd);
	else if (ft_strcmp(command, "export") == 0)
		return (&builtin_export);
	else if (ft_strcmp(command, "unset") == 0)
		return (&builtin_unset);
	else if (ft_strcmp(command, "env") == 0)
		return (&builtin_env);
	else if (ft_strcmp(command, "exit") == 0)
		return (&builtin_env);
	else
		return (NULL);
}
