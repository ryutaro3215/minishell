/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:06:10 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/05/27 21:53:55 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

bool	is_blank(char c)
{
	if (c == '\t' || c == ' ' || c == '\n')
		return (true);
	return (false);
}

bool	jump_space(char **addr, char *input)
{
	if (is_blank(*input))
	{
		while (*input == '\t' || *input == ' ')
			input++;
		*addr = input;
		return (true);
	}
	return (false);
}

bool	is_word(char c)
{
	if (c == '\0')
		return (false);
	return (true);
}

bool	is_ope(char	c)
{
	if (strchr("|<>", c) && c != '\0')
		return (true);
	return (false);
}

t_token	*gen_token(char **addr, char *input)
{
	t_token	*token;
	size_t	len;
	char	*tmp;

	tmp = input;
	len = 0;
	while (!is_blank(*input) && *input != '\0')
	{
		len++;
		input++;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->word = strndup(tmp, len);
	if (is_ope(*tmp))
		token->type = 2;
	else
		token->type = 1;
	token->next = NULL;
	*addr = input;
	return (token);
}

t_token	*init_token(char *input)
{
	t_token	*token;
	t_token	tmp;

	tmp.next = NULL;
	token = &tmp;
	while (*input)
	{
		if (jump_space(&input, input))
			continue ;
		else if (is_ope(*input) || is_word(*input))
		{
			token->next = gen_token(&input, input);
			token = token->next;
		}
		else
			printf("Error\n");
	}
	token->next = (t_token *)malloc(sizeof(t_token));
	token = token->next;
	token->word = NULL;
	token->type = 0;
	token->next = NULL;
	return (tmp.next);
}

int	main(void)
{
	char	*input;
	t_token	*token;

	while(true)
	{
		input = readline("$>");
		token = init_token(input);
		while (token->next != NULL)
		{
			printf("%s ", token->word);
			printf("%d\n", token->type);
			token = token->next;
		}
		add_history(input);
		free(input);
	}
	printf("succes include headr");
	return (0);
}
