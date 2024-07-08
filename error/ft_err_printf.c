/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_err_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:44 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:45 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

static void	err_if_char_p(char *var)
{
	size_t	i;

	if (var == NULL)
	{
		write(2, "(null)", 6);
		return ;
	}
	i = 0;
	while (var[i])
	{
		write(2, &var[i], 1);
		i++;
	}
}

void	ft_err_printf(const char *str, char *var)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[++i] == 's')
				err_if_char_p(var);
		}
		else
			write(2, &str[i], 1);
		i++;
	}
}
