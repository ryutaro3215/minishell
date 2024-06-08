#include "../include/expand.h"

char	*get_last_double_quote(char *word)
{
	word++; // skip first double quote.
	return (ft_strchr(word, '\"'));
}

char	*get_last_single_quote(char *word)
{
	word++; // skip first single quote.
	return (ft_strchr(word, '\''));
}
