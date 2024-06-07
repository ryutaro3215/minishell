#include "../include/builtin.h"

int	builtin_unset(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		return EXECUTION_SUCCESS;
	while (current_token)
	{
		if (environ_already_exist(current_token->name, UNSET))
			unset_environ_var(current_token->name);
		current_token = current_token->next;
	}
	return EXECUTION_SUCCESS;
}
