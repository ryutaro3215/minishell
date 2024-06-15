/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:31 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:32 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expand.h"

char	*get_env_value(char *env_name)
{
	extern char	**environ;
	char		**tmp;
	size_t		i;
	char		*current_name;
	char		*env_value;

	tmp = environ;
	i = 0;
	while (tmp[i])
	{
		current_name = get_environ_name(tmp[i]);
		if (ft_strcmp(current_name, env_name) == 0)
		{
			env_value = get_environ_value(tmp[i]);
			free(current_name);
			return (env_value);
		}
		free(current_name);
		i++;
	}
	return (NULL);
}

char	*get_env_name(char *word)
{
	char	*env_name;

	env_name = NULL;
	word++;
	while (*word && *word != '\'' && *word != '\"'
		&& *word != '$' && *word != ' ' && *word != '\t' && *word != ':')
	{
		env_name = append_char(env_name, *word);
		word++;
	}
	return (env_name);
}

char	*do_each_expand(char *env_name, char *new_word,
	char **old_word, int last_command_exit_status)
{
	if (!env_name)
		new_word = handle_dollar_only(new_word, old_word);
	else if (ft_strncmp(env_name, "?", 1) == 0)
	{
		new_word = handle_question(new_word, old_word,
				last_command_exit_status);
	}
	else
	{
		new_word = handle_environment_variable(new_word,
				old_word, env_name);
	}
	return (new_word);
}

void	expand_dollar(t_token *current_word, int last_command_exit_status)
{
	char	*new_word;
	char	*old_word;
	char	*env_name;

	new_word = NULL;
	old_word = current_word->name;
	while (*old_word)
	{
		if (*old_word == '\'')
			new_word = skip_single_quote(new_word, &old_word);
		else if (*old_word == '\"')
			new_word = handle_inside_double_quote(new_word, &old_word,
					last_command_exit_status);
		else if (*old_word == '$')
		{
			env_name = get_env_name(old_word);
			new_word = do_each_expand(env_name, new_word, &old_word,
					last_command_exit_status);
			free(env_name);
		}
		else
			new_word = skip_char(new_word, &old_word);
	}
	free(current_word->name);
	current_word->name = new_word;
}

void	expand_redirect_dollar(t_redirect *current_redirect,
	int last_command_exit_status)
{
	char	*new_redirect;
	char	*old_redirect;
	char	*env_name;

	new_redirect = NULL;
	old_redirect = current_redirect->filename;
	while (*old_redirect)
	{
		if (*old_redirect == '\'')
			new_redirect = skip_single_quote(new_redirect, &old_redirect);
		else if (*old_redirect == '$')
		{
			env_name = get_env_name(old_redirect);
			new_redirect = do_each_expand(env_name, new_redirect, &old_redirect,
					last_command_exit_status);
			free(env_name);
		}
		else
			new_redirect = skip_char(new_redirect, &old_redirect);
	}
	free(current_redirect->filename);
	current_redirect->filename = new_redirect;
}
