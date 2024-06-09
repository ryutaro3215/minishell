/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:06:10 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/09 17:06:44 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	check_space(char c)
{
	if ((c == ' ' || c == '\t')
		&& (c != '\n' || c != '\0'))
		return (true);
	else
		return (false);
}

bool	check_conope(char c)
{
	if (c == '|' || c == '&')
		return (true);
	else
		return (false);
}

bool	check_redope(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	skip_space(char **str)
{
	while (check_space(**str))
		(*str)++;
}

int	check_quote(char str)
{
	if (str == '\"')
		return (2);
	else if (str == '\'')
		return (1);
	else
		return (0);
}

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
	return (i + 1);
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
			str++;
			len++;
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
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->name = strndup(*str, word_len);
	token->attribute = WORD;
	token->next = NULL;
	*str += word_len;
	return (token);
}

int	get_redope_len(t_token *token, char *str)
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

int	get_conope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	if (str[ope_len] == '|')
	{
		token->attribute = CONNECTION;
		while (str[ope_len] && str[ope_len] == '|')
			ope_len++;
	}
	else
	{
		if (*str == '&' && *(str + 1) == '&')
		{
			token->attribute = CONNECTION;
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

int	get_ope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	if (check_conope(*str))
		ope_len = get_conope_len(token, str);
	else
		ope_len = get_redope_len(token, str);
	return (ope_len);
}

t_token	*new_ope_token(char **str)
{
	t_token	*token;
	int		ope_len;

	ope_len = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ope_len = get_ope_len(token, *str);
	token->name = strndup(*str, ope_len);
	token->next = NULL;
	*str += ope_len;
	return (token);
}

t_token	*init_token(char *str)
{
	t_token	*token;
	t_token	head;

	head.next = NULL;
	token = &head;
	while (*str)
	{
		skip_space(&str);
		if (check_conope(*str) || check_redope(*str))
			token->next = new_ope_token(&str);
		else
			token->next = new_word_token(&str);
		if (!token->next)
			return (NULL);
		token = token->next;
	}
	return (head.next);
}

int main (void)
{
	t_token	*token;
	char	*str;

	while (true)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		token = init_token(str);
		while (token != NULL)
		{
			printf("token: %s\n", token->name);
			printf("type: %d\n", token->attribute);
			token = token->next;
		}
		add_history(str);
	}
}
