/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:38 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:39 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

void	handle_error(bool is_error)
{
	if (is_error && errno != 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (is_error && errno == 0)
	{
		write(2, "minishell: Unknown error\n", 26);
		exit(EXIT_FAILURE);
	}
}
