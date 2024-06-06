#include "../include/exec.h"

t_token	*delete_current_word(t_simple *simple, t_token *current_word)
{
	t_token	*word_list;
	t_token	*tmp;

	if (simple->word_list == current_word)
	{
		tmp = current_word->next;
		free(current_word->name);
		free(current_word);
		simple->word_list = tmp;
		return tmp;
	}
	word_list = simple->word_list;
	while (word_list->next != current_word)
	{
		word_list = word_list->next;
		continue;
	}
	tmp = word_list->next->next;
	free(current_word->name);
	free(current_word);
	word_list->next = tmp;
	return word_list->next;
}

char	*get_env_value(char *env_name)
{
	extern char	**environ;
	char	**tmp;
	size_t	i;
	char	*current_name;
	char	*env_value;

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
	while (*word && *word != '\'' && *word != '\"' && *word != '$')
	{
		env_name = append_char(env_name, *word);
		word++;
	}
	return env_name;
}

char	*get_last_single_quote(char *word)
{
	word++; // skip first single quote.
	return (strchr(word, '\''));
}

char	*append_char(char *word, char c)
{
	char	*new_word;
	size_t	i;

	if (!word)
	{
		new_word = malloc(sizeof(char) * 2);
		new_word[0] = c;
		new_word[1] = '\0';
		return new_word;
	}
	new_word = malloc(sizeof(char) * strlen(word) + 2);
	i = 0;
	while (word[i])
	{
		new_word[i] = word[i];
		i++;
	}
	new_word[i++] = c;
	new_word[i] = '\0';
	free(word);
	return new_word;
}
