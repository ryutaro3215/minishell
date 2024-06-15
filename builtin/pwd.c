/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:15 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:16 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtin.h"

int	builtin_pwd(t_token *word_list)
{
	char	buf[PATH_MAX];

	(void)word_list;
	ft_printf("%s\n", getcwd(buf, PATH_MAX));
	return (EXECUTION_SUCCESS);
}
