/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_something2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:10:38 by kisobe            #+#    #+#             */
/*   Updated: 2024/04/23 18:01:46 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	if_unsigned_decimal(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_put_unsigned_int(arg, p);
	return (count);
}

int	if_hexadec_low(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_put_hexadec_low(arg, p);
	return (count);
}

int	if_hexadec_up(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_put_hexadec_up(arg, p);
	return (count);
}
