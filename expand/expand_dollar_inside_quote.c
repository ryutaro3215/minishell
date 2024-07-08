/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar_inside_quote.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:50 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:51 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expand.h"

char	*handle_inside_double_quote(char *new_word, char **old_word,
	int last_command_exit_status)
{
	char	*env_name;

	new_word = skip_char(new_word, old_word);
	while (**old_word != '\"')
	{
		if (**old_word == '$')
		{
			env_name = get_env_name(*old_word);
			new_word = do_each_expand(env_name, new_word, old_word,
					last_command_exit_status);
			free(env_name);
		}
		else
			new_word = skip_char(new_word, old_word);
	}
	new_word = skip_char(new_word, old_word);
	return (new_word);
}
