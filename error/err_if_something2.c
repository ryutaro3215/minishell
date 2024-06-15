/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_if_something2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:37:35 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:37:36 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/error.h"

int	err_if_unsigned_decimal(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_unsigned_int(arg, p);
	return (count);
}

int	err_if_hexadec_low(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_hexadec_low(arg, p);
	return (count);
}

int	err_if_hexadec_up(va_list ap)
{
	unsigned int	arg;
	int				count;
	int				*p;

	count = 0;
	p = &count;
	arg = va_arg(ap, unsigned int);
	count = ft_err_put_hexadec_up(arg, p);
	return (count);
}
