/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:06:10 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/03 01:11:50 by rmatsuba         ###   ########.fr       */
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

bool	check_ope(char c)
{
	if (c == '|' || c == '<'
		|| c == '>' || c == '&')
		return (true);
	else
		return (false);
}

void	skip_space(char **str)
{
	while (check_space(**str) && check_ope(**str) == 0)
		(*str)++;
}

t_token *new_word_token(char **str)
{
	t_token *token;
	int		word_len;

	word_len = 0;
	while ((*str)[word_len] && !check_space((*str)[word_len])
		&& !check_ope((*str)[word_len]))
		word_len++;
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
	token->type = WORD;
	token->next = NULL;
	*str += word_len;
	return (token);
}

t_token *new_ope_token(char **str)
{
	t_token *token;
	int		ope_len;

	ope_len = 0;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	if (**str == '|')
	{
		token->type = CON_OPE;
		ope_len = 1;
	}
	else
	{
		while((*str)[ope_len] && check_ope((*str)[ope_len]))
			ope_len++;
		token->type = RED_OPE;
	}
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
		if (check_ope(*str))
			token->next = new_ope_token(&str);
		else
			token->next = new_word_token(&str);
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
			token = token->next;
		}
	}
}

