/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_something1_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:12:23 by kisobe            #+#    #+#             */
/*   Updated: 2024/07/20 19:31:24 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

int	ft_put_int(int n, int *p)
{
	char	c;
	long	long_n;

	long_n = n;
	if (long_n < 0)
	{
		long_n *= -1;
		if (write(1, "-", 1) < 0)
			return (-1);
		(*p)++;
	}
	if (10 <= long_n)
	{
		ft_put_int(long_n / 10, p);
	}
	c = long_n % 10 + '0';
	if (*p == -1 || write(1, &c, 1) < 0)
	{
		*p = -1;
		return (-1);
	}
	(*p)++;
	return (*p);
}

int	ft_put_unsigned_int(unsigned int n, int *p)
{
	char	c;

	if (10 <= n)
	{
		ft_put_unsigned_int(n / 10, p);
	}
	c = n % 10 + '0';
	if (*p == -1 || write(1, &c, 1) < 0)
	{
		*p = -1;
		return (-1);
	}
	(*p)++;
	return (*p);
}
