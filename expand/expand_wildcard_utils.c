#include "../include/expand.h"

static void	pattern_match_loop(char **given_word, char **filename, size_t matched_count)
{
	while (**filename)
	{
		if (**given_word == '*')
		{
			(*given_word)++;
			matched_count = 0;
			while (**filename && (**given_word != **filename))
				(*filename)++;
			continue ; // goto next "else if" or "out of while".
		}
		else if (**given_word == **filename)
		{
			(*given_word)++;
			(*filename)++;
			matched_count++;
			continue ; // goto next "if (matched_count..)" or first "if (given...)" or "out of while".
		}
		if (matched_count != 0) // different after some word matched.
		{
			*given_word -= matched_count;
			matched_count = 0;
		}
		else // initial different.
			(*filename)++;
	}
}

bool	pattern_match(char *given_word, char *filename)
{
	size_t	matched_count;

	matched_count = 0;
	pattern_match_loop(&given_word, &filename, matched_count);
	if (*given_word == '*')
		given_word++;
	if (*given_word == '\0' && *filename == '\0')
		return (true);
	return (false);
}
