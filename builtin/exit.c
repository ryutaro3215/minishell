/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:10 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:11 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static size_t	count_words(t_token *word_list)
{
	size_t	count;

	count = 0;
	while (word_list)
	{
		count++;
		word_list = word_list->next;
	}
	return (count);
}

static bool	ft_isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static bool	is_valid_arg(char *arg)
{
	size_t	i;

	i = 0;
	if ((arg[i] == '-' || arg[i] == '+') && arg[i + 1])
		i++;
	while (arg[i])
	{
		if (!ft_isnumber(arg[i]))
		{
			write(2, "minishell: exit: Need number argument\n", 39);
			return (false);
		}
		i++;
	}
	return (true);
}

int	builtin_exit(t_token *word_list, int last_command_exit_status)
{
	size_t	count;

	count = count_words(word_list);
	if (count > 2)
	{
		write(2, "minishell: exit: Too many arguments\n", 37);
		return (EXECUTION_FAILURE);
	}
	write(2, "exit\n", 6);
	if (count == 2 && !is_valid_arg(word_list->next->name))
		exit(2);
	if (!word_list->next)
		exit(last_command_exit_status);
	exit(ft_atoi(word_list->next->name));
}
