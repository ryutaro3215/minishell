/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_something1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:54:25 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:54:26 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

int	if_char(va_list ap)
{
	int	arg;

	arg = va_arg(ap, int);
	return (write(1, &arg, 1));
}

int	if_char_p(va_list ap)
{
	unsigned int	i;
	char			*arg;

	arg = va_arg(ap, char *);
	if (arg == NULL)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	i = 0;
	while (arg[i])
	{
		if (write(1, &arg[i], 1) < 0)
			return (-1);
		i++;
	}
	return (i);
}

int	if_void_p(va_list ap)
{
	uintptr_t	arg;
	int			count;
	int			*p;

	count = 0;
	p = &count;
	arg = (uintptr_t)va_arg(ap, void *);
	if (write(1, "0x", 2) < 0)
		return (-1);
	count += 2;
	count = ft_put_address(arg, p);
	return (count);
}

int	if_decimal(va_list ap)
{
	int	arg;
	int	count;
	int	*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, int);
	count = ft_put_int(arg, p);
	return (count);
}
