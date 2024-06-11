#include "../include_bonus/parse_bonus.h"

t_command	*add_simple_type_command(void)
{
	t_command	*new_command;

	new_command = create_new_command();
	new_command->u_value.simple = create_new_simple();
	new_command->attribute = cm_simple;
	return (new_command);
}

t_command	*add_connection_elem(t_command *new_command,
	t_token *first_token_list, t_token *second_token_list)
{
	new_command->u_value.connection->first = add_command(first_token_list);
	free_token_list(first_token_list);
	if (!new_command->u_value.connection->first)
	{
		free(new_command->u_value.connection);
		free(new_command);
		return (NULL);
	}
	new_command->u_value.connection->second = add_command(second_token_list);
	free_token_list(second_token_list);
	if (!new_command->u_value.connection->second)
	{
		free_command_list(new_command->u_value.connection->first);
		free(new_command->u_value.connection);
		free(new_command);
		return (NULL);
	}
	return (new_command);
}

t_command	*add_connection_type_command(void)
{
	t_command	*new_command;

	new_command = create_new_command();
	new_command->attribute = cm_connection;
	new_command->u_value.connection = create_new_connection();
	return (new_command);
}
