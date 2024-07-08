/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:24 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:52:25 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/expand_bonus.h"

void	expand_words(t_simple *simple, int last_command_exit_status)
{
	t_token	*current_word;
	char	*dollar;

	current_word = simple->word_list;
	while (current_word)
	{
		dollar = ft_strchr(current_word->name, '$');
		if (dollar)
		{
			expand_dollar(current_word, last_command_exit_status);
			if (!current_word->name)
			{
				current_word = delete_current_word(simple, current_word);
				continue ;
			}
		}
		expand_wildcard(current_word);
		remove_quote(current_word);
		current_word = current_word->next;
	}
}

int	expand_redirects(t_simple *simple, int last_command_exit_status)
{
	t_redirect	*current_redirect;
	char		*dollar;

	current_redirect = simple->redirect_list;
	if (!current_redirect->filename)
		return (EXECUTION_SUCCESS);
	while (current_redirect)
	{
		dollar = ft_strchr(current_redirect->filename, '$');
		if (dollar)
		{
			expand_redirect_dollar(current_redirect, last_command_exit_status);
			if (!current_redirect->filename)
			{
				write(2, "minishell: Ambiguous redirect\n", 31);
				return (EXECUTION_FAILURE);
			}
		}
		if (expand_redirect_wildcard(current_redirect) == EXECUTION_FAILURE)
			return (EXECUTION_FAILURE);
		remove_redirect_quote(current_redirect);
		current_redirect = current_redirect->next;
	}
	return (EXECUTION_SUCCESS);
}

int	expand(t_simple *simple, int last_command_exit_status)
{
	expand_words(simple, last_command_exit_status);
	return (expand_redirects(simple, last_command_exit_status));
}
