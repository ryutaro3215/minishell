#include "../include/expand.h"

static char	*remove_single_quote(char *new_word, char **old_word)
{
	char	*last_single_quote;
	char	*inside_single_quote;

	last_single_quote = get_last_single_quote(*old_word);
	(*old_word)++;
	inside_single_quote = ft_substr(*old_word, 0, last_single_quote - *old_word);
	(*old_word) += strlen(inside_single_quote) + 1;
	new_word = ft_strjoin(new_word, inside_single_quote);
	return (new_word);
}

static char	*remove_double_quote(char *new_word, char **old_word)
{
	char	*last_double_quote;
	char	*inside_double_quote;

	last_double_quote = get_last_double_quote(*old_word);
	(*old_word)++;
	inside_double_quote = ft_substr(*old_word, 0, last_double_quote - *old_word);
	*old_word += strlen(inside_double_quote) + 1;
	new_word = ft_strjoin(new_word, inside_double_quote);
	return (new_word);
}

void	remove_quote(t_token *current_word)
{
	char	*old_word;
	char	*new_word;

	old_word = current_word->name;
	if (!strchr(old_word, '\'') && !strchr(old_word, '\"'))
		return ;
	new_word = NULL;
	while (*old_word)
	{
		if (*old_word == '\'')
			new_word = remove_single_quote(new_word, &old_word);
		else if (*old_word == '\"')
			new_word = remove_double_quote(new_word, &old_word);
		else
		{
			new_word = append_char(new_word, *old_word);
			old_word++;
		}
	}
	free(current_word->name);
	current_word->name = new_word;
}
