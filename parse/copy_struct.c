#include "../include/parse.h"

static t_token	*add_word_to_tail(t_token *word_list, t_token *new_word)
{
	t_token	*tmp;

	tmp = word_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_word;
	return word_list;
}

static t_redirect	*add_redirect_to_tail(t_redirect *redirect_list, t_redirect *new_redirect)
{
	t_redirect	*tmp;

	tmp = redirect_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redirect;
	return redirect_list;
}

static t_redirect	*create_redirect_type_struct(t_redirect *redirect_list)
{
	t_redirect	*new_redirect;

	if (redirect_list->filename) // redirect_list has been created.
	{
		new_redirect = malloc(sizeof(t_redirect));
		if (!new_redirect)
		{
			free_redirect_list(redirect_list);
			return NULL;
		}
	}
	else // first redirect_list, but already initialized previous function.
		new_redirect = redirect_list;
	return (new_redirect);
}

t_token	*copy_token(t_token *word_list, t_token *current_token)
{
	t_token	*new_word;

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
		return (add_word_to_tail(word_list, new_word));
}

t_redirect	*copy_redirect(t_redirect *redirect_list, t_token *current_token)
{
	t_redirect	*new_redirect;

	if (strchr(current_token->next->name, '*'))
	{
		printf("minishell: %s: ambiguous redirect\n", current_token->next->name);
		free_redirect_list(redirect_list);
		return NULL;
	}
	new_redirect = create_redirect_type_struct(redirect_list);
	new_redirect->attribute = get_redirect_attribute(current_token->name);
	new_redirect->filename = strdup(current_token->next->name);
	if (!new_redirect->filename)
	{
		free(new_redirect);
		free_redirect_list(redirect_list);
		return NULL;
	}
	new_redirect->next = NULL;
	if (redirect_list == new_redirect)
		return new_redirect;
	else
		return (add_redirect_to_tail(redirect_list, new_redirect));
}

