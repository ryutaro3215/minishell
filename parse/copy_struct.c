/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:40:26 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:40:27 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

static t_token	*add_word_to_tail(t_token *word_list, t_token *new_word)
{
	t_token	*tmp;

	tmp = word_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_word;
	return (word_list);
}

static t_redirect	*add_redirect_to_tail(t_redirect *redirect_list,
	t_redirect *new_redirect)
{
	t_redirect	*tmp;

	tmp = redirect_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redirect;
	return (redirect_list);
}

static t_redirect	*create_redirect_type_struct(t_redirect *redirect_list)
{
	t_redirect	*new_redirect;

	if (redirect_list->filename)
		new_redirect = xmalloc(sizeof(t_redirect));
	else
		new_redirect = redirect_list;
	return (new_redirect);
}

t_token	*copy_token(t_token *word_list, t_token *current_token)
{
	t_token	*new_word;

	new_word = xmalloc(sizeof(t_token));
	new_word->attribute = current_token->attribute;
	new_word->name = ft_strdup(current_token->name);
	new_word->next = NULL;
	if (!word_list)
		return (new_word);
	else
		return (add_word_to_tail(word_list, new_word));
}

t_redirect	*copy_redirect(t_redirect *redirect_list, t_token *current_token)
{
	t_redirect	*new_redirect;

	new_redirect = create_redirect_type_struct(redirect_list);
	new_redirect->attribute = get_redirect_attribute(current_token->name);
	new_redirect->filename = ft_strdup(current_token->next->name);
	new_redirect->next = (NULL);
	if (redirect_list == new_redirect)
		return (new_redirect);
	else
		return (add_redirect_to_tail(redirect_list, new_redirect));
}
