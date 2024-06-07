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
		if (strcmp(current_name, env_name) == 0)
		{
			env_value = get_environ_value(tmp[i]);
			free(current_name);
			return (env_value);
		}
		free(current_name);
		i++;
	}
	return NULL;
}

char	*get_env_name(char *word)
{
	char	*env_name = NULL;

	word++; // skip dollar.
	while (*word && *word != '\'' && *word != '\"' && *word != '$' && *word != ' ' && *word != '\t')
	{
		env_name = append_char(env_name, *word);
		word++;
	}
	return env_name;
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
		else if (*old_word == '$')
		{
			env_name = get_env_name(old_word);
			if (!env_name)
				new_word = handle_dollar_only(new_word, &old_word);
			else if (strcmp(env_name, "?") == 0)
				new_word = handle_question(new_word, &old_word, last_command_exit_status);
			else
				new_word = handle_environment_variable(new_word, &old_word, env_name);
			free(env_name);
		}
		else
			new_word = skip_char(new_word, &old_word);
	}
	free(current_word->name);
	current_word->name = new_word;
}
