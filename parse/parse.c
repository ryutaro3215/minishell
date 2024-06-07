#include "../include/parse.h"

t_command	*add_simple_command(t_token *token_list)
{
	t_command	*new_command;

	new_command = add_simple_type_command();
	new_command->value.simple->redirect_list = create_redirect_list(token_list);
	// if redirect doesn't exist (but not error), redirect_list->filename == NULL
	if (!new_command->value.simple->redirect_list) // malloc or syntax error
	{
		free(new_command->value.simple);
		free(new_command);
		return NULL;
	}
	new_command->value.simple->word_list = create_word_list(token_list);
	// it skip redirect.
	if (!new_command->value.simple->word_list && errno == ENOMEM)
	{
		free_redirect_list(new_command->value.simple->redirect_list);
		free(new_command->value.simple);
		free(new_command);
		return NULL;
	}
	return new_command;
}

t_command	*add_connection(t_token *token_list)
{
	t_command	*new_command;
	t_token	*first_token_list;
	t_token	*second_token_list;

	first_token_list = get_first_token_list(token_list);
	second_token_list = get_second_token_list(token_list);
	if (!first_token_list || !second_token_list) // parse error
	{
		printf("minishell: parse error near '|'\n");
		free_token_list(first_token_list);
		free_token_list(second_token_list);
		return NULL;
	}
	new_command = add_connection_type_command(first_token_list, second_token_list);
	if (!new_command)
		return NULL;
	new_command->value.connection->connector = get_connector(token_list);
	return (add_connection_elem(new_command, first_token_list, second_token_list));
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
		printf("syntax error: %s\n", token_list->name);
		return NULL;
	}
}

t_command	*parse(t_token *token_list)
{
	t_command	*command_list;

	if (!token_list)
		return NULL;
	command_list = add_command(token_list);
	if (!command_list)
		free_token_list(token_list);
	return command_list;
}
