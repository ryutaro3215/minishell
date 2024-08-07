/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:13 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:14 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

static bool	isvalid(char *token_name)
{
	char	*env_name;
	size_t	i;

	if (!ft_strchr(token_name, '='))
		env_name = ft_strdup(token_name);
	else
		env_name = get_environ_name(token_name);
	if (env_name[0] == '\0')
	{
		free(env_name);
		return (false);
	}
	i = 0;
	while (env_name[i])
	{
		if (!ft_isalpha(env_name[i]) && env_name[i] != '_')
		{
			free(env_name);
			return (false);
		}
		i++;
	}
	free(env_name);
	return (true);
}

int	builtin_export(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		builtin_env(NULL);
	while (current_token)
	{
		if (ft_strchr(current_token->name, '=') && isvalid(current_token->name))
		{
			if (environ_already_exist(current_token->name, EXPORT))
				replace_environ_var(current_token->name);
			else
				add_environ_var(current_token->name);
		}
		else
		{
			if (!isvalid(current_token->name))
			{
				write(2, "minishell: export: Invalid identifier\n", 39);
				return (EXECUTION_FAILURE);
			}
		}
		current_token = current_token->next;
	}
	return (EXECUTION_SUCCESS);
}
