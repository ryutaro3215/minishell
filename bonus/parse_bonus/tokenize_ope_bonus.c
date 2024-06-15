/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_ope.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:43:31 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/15 14:09:23 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/parse_bonus.h"

static int	get_redope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	while (*str && check_redope(*str) && !check_conope(*str))
	{
		ope_len++;
		str++;
	}
	token->attribute = REDIRECT;
	return (ope_len);
}

static int	get_conope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	if (str[ope_len] == '|')
	{
		token->attribute = OPERATOR;
		while (str[ope_len] && str[ope_len] == '|')
			ope_len++;
	}
	else
	{
		if (*str == '&' && *(str + 1) == '&')
		{
			token->attribute = OPERATOR;
			ope_len = 2;
		}
		else
		{
			token->attribute = WORD;
			ope_len = get_word_len(str + 1) + 1;
		}
	}
	return (ope_len);
}

static int	get_ope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	if (check_conope(*str))
		ope_len = get_conope_len(token, str);
	else
		ope_len = get_redope_len(token, str);
	return (ope_len);
}

static t_token	*new_ope_token(char **str)
{
	t_token	*token;
	int		ope_len;

	ope_len = 0;
	token = (t_token *)xmalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ope_len = get_ope_len(token, *str);
	token->name = ft_strndup(*str, ope_len);
	token->next = NULL;
	*str += ope_len;
	return (token);
}
