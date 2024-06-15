/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:33 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:51:34 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/error_bonus.h"

void	handle_error(bool is_error)
{
	if (is_error && errno != 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (is_error && errno == 0)
	{
		ft_err_printf("minishell: Unknown error\n");
		exit(EXIT_FAILURE);
	}
}
