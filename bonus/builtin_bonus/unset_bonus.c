/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:14 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:51:15 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/builtin_bonus.h"

int	builtin_unset(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		return (EXECUTION_SUCCESS);
	while (current_token)
	{
		if (environ_already_exist(current_token->name, UNSET))
			unset_environ_var(current_token->name);
		current_token = current_token->next;
	}
	return (EXECUTION_SUCCESS);
}
