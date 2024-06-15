/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:43 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:59:07 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/exec_bonus.h"

void	add_new_word(t_token *current_word, char *filename)
{
	t_token	*new_word;

	if (!current_word->name)
	{
		current_word->name = ft_strdup(filename);
		current_word->attribute = WORD;
		current_word->next = NULL;
		return ;
	}
	while (current_word->next)
		current_word = current_word->next;
	new_word = xmalloc(sizeof(t_token));
	new_word->name = ft_strdup(filename);
	new_word->attribute = WORD;
	new_word->next = NULL;
	current_word->next = new_word;
}

t_token	*delete_current_word(t_simple *simple, t_token *current_word)
{
	t_token	*word_list;
	t_token	*tmp;

	if (simple->word_list == current_word)
	{
		tmp = current_word->next;
		free(current_word->name);
		free(current_word);
		simple->word_list = tmp;
		return (tmp);
	}
	word_list = simple->word_list;
	while (word_list->next != current_word)
	{
		word_list = word_list->next;
		continue ;
	}
	tmp = word_list->next->next;
	free(current_word->name);
	free(current_word);
	word_list->next = tmp;
	return (word_list->next);
}

char	*append_char(char *word, char c)
{
	char	*new_word;
	size_t	i;

	if (!word)
	{
		new_word = xmalloc(sizeof(char) * 2);
		new_word[0] = c;
		new_word[1] = '\0';
		return (new_word);
	}
	new_word = xmalloc(sizeof(char) * ft_strlen(word) + 2);
	i = 0;
	while (word[i])
	{
		new_word[i] = word[i];
		i++;
	}
	new_word[i++] = c;
	new_word[i] = '\0';
	free(word);
	return (new_word);
}
