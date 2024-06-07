#include "../include/parse.h"

t_command	*add_simple_type_command(void)
{
	t_command	*new_command;

	new_command = create_new_command();
	if (!new_command)
		return NULL;
	new_command->value.simple = create_new_simple();
	if (!new_command->value.simple)
	{
		free(new_command);
		return NULL;
	}
	new_command->attribute = cm_simple;
	return new_command;
}

t_command	*add_connection_elem(t_command *new_command, t_token *first_token_list, t_token *second_token_list)
{
	new_command->value.connection->first = add_command(first_token_list);
	free_token_list(first_token_list);
	if (!new_command->value.connection->first)
	{
		free(new_command->value.connection);
		free(new_command);
		return NULL;
	}
	new_command->value.connection->second = add_command(second_token_list);
	free_token_list(second_token_list);
	if (!new_command->value.connection->second)
	{
		free_command_list(new_command->value.connection->first);
		free(new_command->value.connection);
		free(new_command);
		return NULL;
	}
	return new_command;
}

t_command	*add_connection_type_command(t_token *first_token_list, t_token *second_token_list)
{
	t_command	*new_command;

	new_command = create_new_command();
	if (!new_command)
	{
		free_token_list(first_token_list);
		free_token_list(second_token_list);
		return NULL;
	}
	new_command->attribute = cm_connection;
	new_command->value.connection = create_new_connection();
	if (!new_command->value.connection)
	{
		free_token_list(first_token_list);
		free_token_list(second_token_list);
		free(new_command);
		return NULL;
	}
	return new_command;
}

