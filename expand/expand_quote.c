/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:36 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:37 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expand.h"

static char	*remove_single_quote(char *new_word, char **old_word)
{
	char	*last_single_quote;
	char	*inside_single_quote;

	last_single_quote = get_last_single_quote(*old_word);
	(*old_word)++;
	inside_single_quote = ft_substr(*old_word, 0,
			last_single_quote - *old_word);
	(*old_word) += ft_strlen(inside_single_quote) + 1;
	new_word = ft_strjoin(new_word, inside_single_quote);
	return (new_word);
}

static char	*remove_double_quote(char *new_word, char **old_word)
{
	char	*last_double_quote;
	char	*inside_double_quote;

	last_double_quote = get_last_double_quote(*old_word);
	(*old_word)++;
	inside_double_quote = ft_substr(*old_word, 0,
			last_double_quote - *old_word);
	*old_word += ft_strlen(inside_double_quote) + 1;
	new_word = ft_strjoin(new_word, inside_double_quote);
	return (new_word);
}

void	remove_quote(t_token *current_word)
{
	char	*old_word;
	char	*new_word;

	old_word = current_word->name;
	if (!ft_strchr(old_word, '\'') && !ft_strchr(old_word, '\"'))
		return ;
	new_word = NULL;
	while (*old_word)
	{
		if (*old_word == '\'')
			new_word = remove_single_quote(new_word, &old_word);
		else if (*old_word == '\"')
			new_word = remove_double_quote(new_word, &old_word);
		else
		{
			new_word = append_char(new_word, *old_word);
			old_word++;
		}
	}
	free(current_word->name);
	current_word->name = new_word;
}

void	remove_redirect_quote(t_redirect *current_redirect)
{
	char	*old_redirect;
	char	*new_redirect;

	old_redirect = current_redirect->filename;
	if (!ft_strchr(old_redirect, '\'') && !ft_strchr(old_redirect, '\"'))
		return ;
	new_redirect = NULL;
	while (*old_redirect)
	{
		if (*old_redirect == '\'')
			new_redirect = remove_single_quote(new_redirect, &old_redirect);
		else if (*old_redirect == '\"')
			new_redirect = remove_double_quote(new_redirect, &old_redirect);
		else
		{
			new_redirect = append_char(new_redirect, *old_redirect);
			old_redirect++;
		}
	}
	free(current_redirect->filename);
	current_redirect->filename = new_redirect;
}
