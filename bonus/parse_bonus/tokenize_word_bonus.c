/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_word_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:44:13 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/15 14:24:22 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/parse_bonus.h"

int	skip_next_quote(char *str)
{
	int	quote_type;
	int	i;

	i = 0;
	quote_type = check_quote(str[i]);
	i++;
	if (quote_type == 2)
	{
		while (str[i] && check_quote(str[i]) != 2)
			i++;
	}
	else
	{
		while (str[i] && check_quote(str[i]) != 1)
			i++;
	}
	if (str[i] == '\0')
		return (0);
	return (++i);
}

int	get_word_len(char *str)
{
	int	len;
	int	quote_len;

	len = 0;
	quote_len = 0;
	while (*str && !check_space(*str) && !check_conope(*str)
		&& !check_redope(*str))
	{
		if (check_quote(*str))
		{
			quote_len = skip_next_quote(str);
			if (quote_len == 0)
				return (0);
			str += quote_len;
			len += quote_len;
		}
		else
		{
			str++;
			len++;
		}
	}
	return (len);
}

t_token	*new_word_token(char **str)
{
	t_token	*token;
	int		word_len;

	word_len = get_word_len(*str);
	if (word_len == 0)
		return (NULL);
	token = (t_token *)xmalloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->name = ft_strndup(*str, word_len);
	token->attribute = WORD;
	token->next = NULL;
	*str += word_len;
	return (token);
}
