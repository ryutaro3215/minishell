#include "../include/parse.h"

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

t_redirect	*copy_redirect(t_redirect *redirect_list, t_token *current_token)
{
	t_redirect	*new_redirect;
	t_redirect	*tmp;

	if (strchr(current_token->next->name, '*'))
	{
		printf("minishell: %s: ambiguous redirect\n", current_token->next->name);
		free_redirect_list(redirect_list);
		return NULL;
	}
	if (redirect_list->filename) // redirect_list has been created.
	{
		new_redirect = malloc(sizeof(t_redirect));
		if (!new_redirect)
		{
			free_redirect_list(redirect_list);
			return NULL;
		}
	}
	else // first redirect_list, but alread initialized previous function.
		new_redirect = redirect_list;
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
	{
		tmp = redirect_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_redirect;
		return redirect_list;
	}
}

