#include "../include/builtin.h"

int	builtin_export(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		builtin_env(NULL);
	while (current_token)
	{
		if (ft_strchr(current_token->name, '='))
		{
			if (ft_strcmp(current_token->name, "=") == 0)
			{
				ft_err_printf("minishell: export: Invalid identifier\n");
				return (EXECUTION_FAILURE);
			}
			if (environ_already_exist(current_token->name, EXPORT))
				replace_environ_var(current_token->name);
			else
				add_environ_var(current_token->name);
		}
		current_token = current_token->next;
	}
	return (EXECUTION_SUCCESS);
}
