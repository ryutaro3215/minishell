/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:54:48 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:54:49 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/parse_bonus.h"

t_command	*parse_command(char *line)
{
	t_token		*token_list;
	t_command	*command_list;

	token_list = tokenize(line);
	command_list = parse(token_list);
	if (!command_list)
		return (NULL);
	if (need_here_document(token_list))
	{
		if (gather_here_document(command_list) == HEREDOC_FAILURE)
		{
			free_token_list(token_list);
			free_command_list(command_list);
			return (NULL);
		}
	}
	free_token_list(token_list);
	return (command_list);
}
