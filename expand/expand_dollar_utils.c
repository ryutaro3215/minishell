#include "../include/expand.h"

char	*skip_single_quote(char *new_word, char **old_word)
{
	char	*last_single_quote;
	char	*inside_single_quote;

	last_single_quote = get_last_single_quote(*old_word);
	inside_single_quote = ft_substr(*old_word, 0, last_single_quote - *old_word + 1);
	(*old_word) += strlen(inside_single_quote);
	return (ft_strjoin(new_word, inside_single_quote));
}

char	*handle_dollar_only(char *new_word, char **old_word)
{
	new_word = append_char(new_word, **old_word);
	(*old_word)++;
	return (new_word);
}

char	*handle_question(char *new_word, char **old_word, int last_command_exit_status)
{
	char	*exit_status;

	exit_status = ft_itoa(last_command_exit_status);
	new_word = ft_strjoin(new_word, exit_status);
	(*old_word) += 2; // $?
	return (new_word);
}

char	*handle_environment_variable(char *new_word, char **old_word, char *env_name)
{
	char	*env_value;

	env_value = get_env_value(env_name);
	if (!env_value)
		(*old_word) += strlen(env_name) + 1; // 1 is num of "$".
	else
	{
		(*old_word) += strlen(env_name) + 1;
		new_word = ft_strjoin(new_word, env_value);
	}
	return (new_word);
}

char	*skip_char(char *new_word, char ** old_word)
{
	new_word = append_char(new_word, **old_word);
	(*old_word)++;
	return (new_word);
}

