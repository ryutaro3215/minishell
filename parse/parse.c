#include "parse.h"

int	detect_cm_attribute(t_token *token_list)
{
	while (token_list->next)
	{
		if (token_list->attribute == OPERATOR)
		{
			if (strcmp(token_list->name, "|") == 0)
				return cm_connection;
			// you can add other operations('||' '&&' '&').
		}
		token_list = token_list->next;
	}
	return (cm_simple);
}

t_command	*create_new_command()
{
	t_command	*new_command;

	new_command = malloc(sizeof(t_command));
	return new_command;
}

t_simple	*create_new_simple()
{
	t_simple	*simple;

	simple = malloc(sizeof(t_simple));
	return simple;
}

t_connection	*create_new_connection()
{
	t_connection	*connection;

	connection = malloc(sizeof(connection));
	return connection;
}

t_token	*copy_token(t_token *word_list, t_token *current_token)
{
	t_token	*new_word;
	t_token	*tmp;

	new_word = malloc(sizeof(t_token));
	if (!new_word)
	{
		free_token_list(word_list);
		return NULL;
	}
	new_word->attribute = current_token->attribute;
	new_word->name = strdup(current_token->name);
	if (!new_word->name)
	{
		free(new_word);
		free_token_list(word_list);
		return NULL;
	}
	new_word->next = NULL;
	if (!word_list)
		return new_word;
	else
	{
		tmp = word_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_word;
		return word_list;
	}
}

t_token	*create_word_list(t_token *token_list)
{
	t_token	*current_token = token_list;
	t_token	*word_list = NULL;

	while (current_token && current_token->attribute != OPERATOR)
	{
		// create null terminated word list.
		word_list = copy_token(word_list, current_token);
		if (!word_list)
			return NULL;
		current_token = current_token->next;
	}
	return word_list;
}

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
	new_command->value.simple->word_list = create_word_list(token_list);
	if (!new_command->value.simple)
	{
		free(new_command);
		free(new_command->value.simple);
		return NULL;
	}
#ifdef DEBUG
	printf("simple_command:\n");
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

t_token	*get_first_token_list(t_token *token_list)
{
	return (create_word_list(token_list));
}

t_token	*get_second_token_list(t_token *token_list)
{
	t_token	*current_token;
	t_token	*second_token_list = NULL;

	while (token_list && token_list->attribute != OPERATOR)
		token_list = token_list->next;
	if (!token_list)
		return NULL;
	current_token = token_list->next; // next to operation(head of second_token_list).
	while (current_token)
	{
		second_token_list = copy_token(second_token_list, current_token);
		if (!second_token_list)
			return NULL;
		current_token = current_token->next;
	}
	return second_token_list;
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
		printf("syntax error: %s\n", token_list->name);
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
#ifdef DEBUG
	printf("first_token:\n");
#endif
	new_command->value.connection->first = add_command(first_token_list);
#ifdef DEBUG
	printf("second_token:\n");
#endif
	new_command->value.connection->second = add_command(second_token_list);
	free_token_list(first_token_list);
	free_token_list(second_token_list);
	return new_command;
}

t_command	*add_command(t_token *token_list)
{
	int	cm_attribute;

	cm_attribute = detect_cm_attribute(token_list);
	if (cm_attribute == cm_simple)
	{
#ifdef DEBUG
		printf("simple:\n");
#endif
		return (add_simple_command(token_list));
	}
	else if (cm_attribute == cm_connection)
	{
#ifdef DEBUG
		printf("connection:\n");
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
	return command_list;
}
