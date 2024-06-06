#include "../include/parse.h"

int	get_cm_attribute(t_token *token_list)
{
	while (token_list)
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

int	get_redirect_attribute(char *redirect_name)
{
	if (strcmp(redirect_name, "<") == 0)
		return r_input;
	else if (strcmp(redirect_name, ">") == 0)
		return r_output;
	else if (strcmp(redirect_name, "<<") == 0)
		return r_heredoc;
	else // (strcmp(redirect_name, ">>") == 0)
		return r_append_output;
}

int	get_connector(t_token *token_list)
{
	while (token_list && token_list->attribute != OPERATOR)
		token_list = token_list->next;
	//if (!token_list) already checked in get_second_token_list()
	//	return NULL; 
	if (strcmp(token_list->name, "|") == 0)
		return pipeline;
	printf("Invalid connector added\n");
	return -1;
}

t_token	*get_first_token_list(t_token *token_list)
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

t_token	*get_second_token_list(t_token *token_list)
{
	t_token	*current_token;
	t_token	*second_token_list = NULL;

	while (token_list && token_list->attribute != OPERATOR)
		token_list = token_list->next;
	if (!token_list || !token_list->next)
		return NULL;
	current_token = token_list->next;
	// next to operation(head of second_token_list).
	if (current_token->attribute != WORD && current_token->attribute != REDIRECT)
		return NULL;
	while (current_token)
	{
		second_token_list = copy_token(second_token_list, current_token);
		if (!second_token_list)
			return NULL;
		current_token = current_token->next;
	}
	return second_token_list;
}
