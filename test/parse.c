/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:47:54 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/07 23:57:38 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_com_attr(t_token *token)
{
	while (token)
	{
		if (token->attr == CON_OPE)
			return (CON_OPE);
		token = token->next;
	}
	return (SIMPLE_COMMAND);
}

t_token	*tokendup(t_token *token)
{
	t_token	*dup_token;
	t_token	head;

	dup_token = &head;
	head.next = NULL;
	while (token)
	{
		dup_token->next = (t_token *)malloc(sizeof(t_token));
		dup_token->next->word = strdup(token->word);
		dup_token->next->attr = token->attr;
		token = token->next;
		dup_token = dup_token->next;
	}
	return (head.next);
}

t_simple	*new_simple(t_token *token)
{
	t_simple	*new_simple;

	new_simple = (t_simple *)malloc(sizeof(t_simple));
	new_simple->token = tokendup(token);
	return (new_simple);
}

t_command	*make_simple_command(t_token *token)
{
	t_command	*new_simplecom;

	new_simplecom = (t_command *)malloc(sizeof(t_command));
	new_simplecom->com_attr = SIMPLE_COMMAND;
	new_simplecom->command = new_simple(token);
	return (new_simplecom);
}

t_token	*make_prevtoken(t_token *token)
{
	t_token	*prev_token;
	t_token	*head;

	head = token;
	while (token)
	{
		if (token->next->attr == CON_OPE);
		{
			token->next = NULL;
			break ;
		}
		token = token->next;
	}
	prev_token = tokendup(head); 
	return (prev_token);
}

t_token	*make_nexttoken(t_token *token)
{
	t_token	*next_token;

	while (token)
	{
		if (token->attr == CON_OPE)
		{
			token = token->next;
			break ;
		}
		token = token->next;
	}
	next_token = tokendup(token);
	return (next_token);
}
t_connector	*new_connector(t_token *token)
{
	t_connector	*new_connector;
	t_token	*prev;
	t_toke	*next;

	prev = make_prevtoken(token);
	next = make_nexttoken(token);
	new_connector = (t_connector *)malloc(sizeof(t_connector));
	new_connector->left = make_command_struct(prev);
	new_connector->right = make_command_struct(next);
	return (new_connector);
}

t_command	*make_ope_command(t_token *token)
{
	t_command	*new_opecom;

	new_opecom = (t_command *)malloc(sizeof(t_command));
	new_opecom->com_attr = CONNECTOR;
	new_opecom->command = new_connector(t_token);
	return (new_opecom);
}

t_command	*make_command_struct(t_token *token)
{
	int	command_attr;

	command_attr = check_com_attr(token);
	if (command_attr == SIMPLE)
	{
		return (make_simple_command(token));
	else if (command_attr == CON_OPE)
	{
		return (make_ope_command(token));
	}
	else
		return (NULL);
}

t_command	*make_command(t_token *token)
{
	t_command	*command;

	command = make_command_struct();
	return (command);
}
