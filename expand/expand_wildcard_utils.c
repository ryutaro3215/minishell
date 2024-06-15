/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:44 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:45 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expand.h"

static void	pattern_match_loop(char **given_word, char **filename,
	size_t matched_count)
{
	while (**filename)
	{
		if (**given_word == '*')
		{
			(*given_word)++;
			matched_count = 0;
			while (**filename && (**given_word != **filename))
				(*filename)++;
			continue ;
		}
		else if (**given_word == **filename)
		{
			(*given_word)++;
			(*filename)++;
			matched_count++;
			continue ;
		}
		if (matched_count != 0)
		{
			*given_word -= matched_count;
			matched_count = 0;
		}
		else
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
