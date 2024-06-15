/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:52 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 14:00:40 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/free_bonus.h"

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->name);
		free(token_list);
		token_list = tmp;
	}
}

void	free_redirect_list(t_redirect *redirect_list)
{
	t_redirect	*tmp;

	while (redirect_list)
	{
		tmp = redirect_list->next;
		free(redirect_list->filename);
		free(redirect_list);
		redirect_list = tmp;
	}
}

void	free_simple(t_command *command)
{
	free_token_list(command->u_value.simple->word_list);
	free_redirect_list(command->u_value.simple->redirect_list);
	free(command->u_value.simple);
	free(command);
}

void	free_command_list(t_command *command_list)
{
	if (command_list->attribute == cm_simple)
		free_simple(command_list);
	else
	{
		free_command_list(command_list->u_value.connection->first);
		free_command_list(command_list->u_value.connection->second);
		free(command_list->u_value.connection);
		free(command_list);
	}
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
