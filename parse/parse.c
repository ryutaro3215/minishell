<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:47:54 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/06 21:41:16 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	check_com_attr(t_token *token)
{
	int	command_attr;

	while (token)
	{
		if (token->attr = CON_OPE)
			return (CON_OPE);
		token = token->next;
	}
	return (SIMPLE);
}

t_token	*tokendup(t_token *token)
{
	t_token	*dup_token;
	t_token	head;
	int	i;

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
	new_simplecom->com_attr = SIMPLE_COMMOND;
	new_simplecom->command = new_simple(t_token);
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
=======
#include "../include/parse.h"

t_command	*add_simple_command(t_token *token_list)
{
	t_command	*new_command;

	new_command = add_simple_type_command();
	new_command->u_value.simple->redirect_list = create_redirect_list(token_list);
	// if redirect doesn't exist (but not error), redirect_list->filename == NULL
	if (!new_command->u_value.simple->redirect_list) // malloc or syntax error
	{
		free(new_command->u_value.simple);
		free(new_command);
		return (NULL);
	}
	new_command->u_value.simple->word_list = create_word_list(token_list);
	// it skip redirect.
	if (!new_command->u_value.simple->word_list && errno == ENOMEM)
	{
		free_redirect_list(new_command->u_value.simple->redirect_list);
		free(new_command->u_value.simple);
		free(new_command);
		return (NULL);
	}
	return (new_command);
}

t_command	*add_connection(t_token *token_list)
{
	t_command	*new_command;
	t_token		*first_token_list;
	t_token		*second_token_list;

	first_token_list = get_first_token_list(token_list);
	second_token_list = get_second_token_list(token_list);
	if (!first_token_list || !second_token_list) // parse error
	{
		ft_err_printf("minishell: parse error near '|'\n");
		free_token_list(first_token_list);
		free_token_list(second_token_list);
		return (NULL);
	}
	new_command = add_connection_type_command();
	if (!new_command)
		return (NULL);
	new_command->u_value.connection->connector = get_connector(token_list);
	return (add_connection_elem(new_command, first_token_list,
			second_token_list));
}

t_command	*add_command(t_token *token_list)
{
	int	cm_attribute;

	cm_attribute = get_cm_attribute(token_list);
	if (cm_attribute == cm_simple)
		return (add_simple_command(token_list));
	else if (cm_attribute == cm_connection)
		return (add_connection(token_list));
	else
	{
		ft_err_printf("minishell: syntax error: %s\n", token_list->name);
		return (NULL);
	}
}

t_command	*parse(t_token *token_list)
{
	t_command	*command_list;

	if (!token_list)
		return (NULL);
	command_list = add_command(token_list);
	if (!command_list)
		free_token_list(token_list);
	return (command_list);
>>>>>>> c232153d4ee13c5cb9f7a8f6bb9a920e572a0112
}
