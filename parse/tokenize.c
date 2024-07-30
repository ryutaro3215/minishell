/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:43:20 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/07/30 17:33:34 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

t_token	*tokenize(char *line)
{
	t_token	*token;
	t_token	head;

	head.next = NULL;
	token = &head;
	while (*line)
	{
		skip_space(&line);
		if (*line == '\0')
			break ;
		if (check_conope(*line) || check_redope(*line))
			token->next = new_ope_token(&line);
		else
			token->next = new_word_token(&line);
		if (!token->next)
		{
			free_token_list(head.next);
			return (NULL);
		}
		token = token->next;
	}
	return (head.next);
}
