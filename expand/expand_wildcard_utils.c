#include "../include/expand.h"

bool	pattern_match(char *given_word, char *filename)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (given_word[i] && filename[j])
	{
		if (given_word[i] == '*')
		{
			i++;
			while (filename[j] && (given_word[i] != filename[j]))
				j++;
			continue;
		}
		else if (given_word[i] == filename[j])
		{
			i++;
			j++;
			continue;
		}
		else
			break;
	}
	if (given_word[i] == '\0' && filename[j] == '\0')
		return true;
	return false;
}

