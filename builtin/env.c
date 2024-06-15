/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:08 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:09 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

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
