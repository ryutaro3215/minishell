#include "../include/expand.h"

void	expand_words(t_simple *simple, int last_command_exit_status)
{
	t_token	*current_word;
	char	*dollar;

	current_word = simple->word_list;
	while (current_word)
	{
		dollar = ft_strchr(current_word->name, '$');
		if (dollar)
		{
			expand_dollar(current_word, last_command_exit_status);
			if (!current_word->name)
			{
				current_word = delete_current_word(simple, current_word);
				continue ;
			}
		}
		expand_wildcard(current_word);
		remove_quote(current_word);
		current_word = current_word->next;
	}
}
