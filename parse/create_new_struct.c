#include "../include/parse.h"

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

	connection = malloc(sizeof(t_connection));
	return connection;
}

t_redirect	*create_redirect_list(t_token *token_list)
{
	t_token	*current_token = token_list;
	t_redirect	*redirect_list = malloc(sizeof(t_redirect));
	redirect_list->filename = NULL;
	redirect_list->next = NULL;

	while (current_token && current_token->attribute != OPERATOR)
	{
		if (current_token->attribute == REDIRECT)
		{
			if (!current_token->next || current_token->next->attribute != WORD)
			{
				printf("minishell: parse error near '%s'\n", current_token->name);
				free_redirect_list(redirect_list);
				return NULL;
			}
			redirect_list = copy_redirect(redirect_list, current_token);
			if (!redirect_list)
			{
				printf("malloc error: %s\n", current_token->name);
				return NULL;
			}
			current_token = current_token->next->next;
		}
		else
			current_token = current_token->next;
	}
	return redirect_list;
}

t_token	*create_word_list(t_token *token_list)
{
	t_token	*current_token = token_list;
	t_token	*word_list = NULL;

	while (current_token && current_token->attribute != OPERATOR)
	{
		if (current_token->attribute == REDIRECT)
			current_token = current_token->next->next;
		else
		{
			// create null terminated word list.
			word_list = copy_token(word_list, current_token);
			if (!word_list)
				return NULL;
			current_token = current_token->next;
		}
	}
	return word_list;
}
