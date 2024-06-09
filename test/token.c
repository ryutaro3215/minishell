/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:06:10 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/07 23:45:35 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (c == '|')
		return (true);
	else
		return (false);
}

bool	check_redope(char c)
{
	if (c == '<' || c == '>' || c == '&')
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
		if (str[i] && check_quote(str[i]) == 2 && check_quote(str[i + 1]) == 2)
			i += skip_next_quote(str + i + 1) + 1;
	}
	else
	{
		while (str[i] && check_quote(str[i]) != 1)
			i++;
		if (str[i] && check_quote(str[i]) == 1 && check_quote(str[i + 1]) == 1)
			i += skip_next_quote(str + i + 1) + 1;
	}
	if (str[i] == '\0')
		return (0);
	return (i);
}

int	get_word_len(char *str)
{
	int	len;

	len = 0;
	if(check_quote(str[len]) != 0)
		len = skip_next_quote(str) + 1;
	else
	{
		while (str[len] && !check_space(str[len]) && !check_conope(str[len])
				&& !check_redope(str[len]))
			len++;
		if (str[len - 1] == '\"' || str[len - 1] == '\'')
			len = 0;
	}
	return (len);
}

t_token *new_word_token(char **str)
{
	t_token *token;
	int		word_len;

	word_len = get_word_len(*str);
	if (word_len == 0)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!token->word)
	{
		free(token);
		return (NULL);
	}
	token->word = strndup(*str, word_len);
	token->attr = WORD;
	token->next = NULL;
	*str += word_len;
	return (token);
}

int	get_ope_len(t_token *token, char *str)
{
	int	ope_len;

	ope_len = 0;
	if (*str == '|')
	{
		token->attr = CON_OPE;
		ope_len = 1;
	}
	else
	{
		while(*str && check_redope(*str) && !check_conope(*str))
		{
			ope_len++;
			str++;
		}
		token->attr = RED_OPE;
	}
	return (ope_len);
}

t_token *new_ope_token(char **str)
{
	t_token *token;
	int		ope_len;

	ope_len = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ope_len = get_ope_len(token, *str);
	token->word = (char *)malloc(sizeof(char) * (ope_len + 1));
	if (!token->word)
	{
		free(token);
		return (NULL);
	}
	token->word = strndup(*str, ope_len);
	token->next = NULL;
	*str += ope_len;
	return (token);
}

t_token *init_token(char *str)
{
	t_token *token;
	t_token head;

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

int main(void)
{
	t_token *token;
	char *str;

	while (true)
	{
		str = readline("minishell$ ");
		if (!str)
			break ;
		token = init_token(str);
		while (token != NULL)
		{
			printf("token: %s\n", token->word);
			printf("type: %d\n", token->attr);
			token = token->next;
		}
		add_history(str);
	}
}

