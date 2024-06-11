#include "../include_bonus/parse_bonus.h"

t_command	*create_new_command(void)
{
	t_command	*new_command;

	new_command = xmalloc(sizeof(t_command));
	return (new_command);
}

t_simple	*create_new_simple(void)
{
	t_simple	*simple;

	simple = xmalloc(sizeof(t_simple));
	return (simple);
}

t_connection	*create_new_connection(void)
{
	t_connection	*connection;

	connection = xmalloc(sizeof(t_connection));
	return (connection);
}

t_redirect	*create_redirect_list(t_token *token_list)
{
	t_redirect	*redirect_list;

	redirect_list = xmalloc(sizeof(t_redirect));
	redirect_list->filename = NULL;
	redirect_list->next = NULL;
	while (token_list && token_list->attribute != OPERATOR)
	{
		if (token_list->attribute == REDIRECT)
		{
			if (!token_list->next || token_list->next->attribute != WORD)
			{
				ft_err_printf("minishell: parse error near '%s'\n",
					token_list->name);
				free_redirect_list(redirect_list);
				return (NULL);
			}
			redirect_list = copy_redirect(redirect_list, token_list);
			if (!redirect_list)
				return (NULL);
		}
		token_list = token_list->next;
	}
	return (redirect_list);
}

t_token	*create_word_list(t_token *token_list)
{
	t_token	*current_token;
	t_token	*word_list;

	current_token = token_list;
	word_list = NULL;
	while (current_token && current_token->attribute != OPERATOR)
	{
		if (current_token->attribute == REDIRECT)
			current_token = current_token->next->next;
		else
		{
			// create null terminated word list.
			word_list = copy_token(word_list, current_token);
			if (!word_list)
				return (NULL);
			current_token = current_token->next;
		}
	}
	return (word_list);
}
