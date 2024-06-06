#include "../include/parse.h"

t_command	*add_simple_command(t_token *token_list)
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
	new_command->value.simple->redirect_list = create_redirect_list(token_list);
	// if redirect doesn't exist (but not error), redirect_list->filename == NULL
	if (!new_command->value.simple->redirect_list) // malloc or syntax error
	{
		free(new_command->value.simple);
		free(new_command);
		return NULL;
	}
#ifdef DEBUG
	t_redirect	*r_tmp = new_command->value.simple->redirect_list;
	printf("redirect_list: ");
	while (r_tmp)
	{
		if (r_tmp->filename)
		{
			printf("%s(%s) -> ", r_tmp->filename, 
			r_tmp->attribute==0 ? "<" : r_tmp->attribute==1 ? ">" : r_tmp->attribute==2 ? "<<" : ">>");
		}
		r_tmp = r_tmp->next;
	}
	printf("(null)\n");
#endif
	new_command->value.simple->word_list = create_word_list(token_list);
	// it skip redirect.
	if (!new_command->value.simple->word_list && errno == ENOMEM)
	{
		free_redirect_list(new_command->value.simple->redirect_list);
		free(new_command->value.simple);
		free(new_command);
		return NULL;
	}
#ifdef DEBUG
	t_token	*tmp = new_command->value.simple->word_list;
	while (tmp)
	{
		printf("%s -> ", tmp->name);
		tmp = tmp->next;
	}
	printf("(null)\n\n");
#endif
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
	new_command->value.connection->connector = get_connector(token_list);
#ifdef DEBUG
	printf("connector: %s\n\n", new_command->value.connection->connector==0 ? "pipeline":"unknown");
	printf("first command\n");
#endif
	new_command->value.connection->first = add_command(first_token_list);
	free_token_list(first_token_list);
	if (!new_command->value.connection->first)
	{
		free(new_command->value.connection);
		free(new_command);
		return NULL;
	}
#ifdef DEBUG
	printf("|\nv\nsecond command\n");
#endif
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

t_command	*add_command(t_token *token_list)
{
	int	cm_attribute;

	cm_attribute = get_cm_attribute(token_list);
	if (cm_attribute == cm_simple)
	{
#ifdef DEBUG
		printf("attribute: cm_simple\n");
#endif
		return (add_simple_command(token_list));
	}
	else if (cm_attribute == cm_connection)
	{
#ifdef DEBUG
		printf("attribute: cm_connection\n");
#endif
		return (add_connection(token_list));
	}
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
