/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_something2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 11:10:38 by kisobe            #+#    #+#             */
/*   Updated: 2024/07/20 19:32:02 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

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
