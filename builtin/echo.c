/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:05 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:06 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	builtin_echo(t_token *word_list)
{
	t_token	*current_word;
	int		n_option_flag;

	current_word = word_list->next;
	if (!current_word)
	{
		ft_printf("\n");
		return (EXECUTION_SUCCESS);
	}
	n_option_flag = 0;
	if (ft_strcmp(current_word->name, "-n") == 0)
	{
		n_option_flag = 1;
		current_word = current_word->next;
	}
	while (current_word)
	{
		ft_printf("%s", current_word->name);
		current_word = current_word->next;
		if (current_word)
			ft_printf(" ");
	}
	if (!n_option_flag)
		ft_printf("\n");
	return (EXECUTION_SUCCESS);
}
