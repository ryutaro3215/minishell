/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:03 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:51:04 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/builtin_bonus.h"

int	builtin_env(t_token *word_list)
{
	extern char	**environ;
	char		**tmp;

	(void)word_list;
	tmp = environ;
	if (tmp)
	{
		while (*tmp)
		{
			ft_printf("%s\n", *tmp);
			tmp++;
		}
	}
	return (EXECUTION_SUCCESS);
}
