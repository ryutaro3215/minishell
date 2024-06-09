/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:51:20 by kisobe            #+#    #+#             */
/*   Updated: 2024/04/23 17:56:36 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	handle_c_to_p(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'c')
	{
		return_tmp = if_char(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 's')
	{
		return_tmp = if_char_p(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'p')
	{
		return_tmp = if_void_p(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
}

void	handle_d_to_u(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'd' || str[*i_p + 1] == 'i')
	{
		return_tmp = if_decimal(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'u')
	{
		return_tmp = if_unsigned_decimal(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
}

void	handle_x_to_per(va_list ap, const char *str, unsigned int *i_p,
		int *num_of_bytes_p)
{
	int	return_tmp;

	if (str[*i_p + 1] == 'x')
	{
		return_tmp = if_hexadec_low(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == 'X')
	{
		return_tmp = if_hexadec_up(ap);
		if (return_tmp < 0)
			*num_of_bytes_p = -1;
		*num_of_bytes_p += return_tmp;
	}
	else if (str[*i_p + 1] == '%')
	{
		if (write(1, "%", 1) < 0)
			*num_of_bytes_p = -1;
		else
			(*num_of_bytes_p)++;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list			ap;
	unsigned int	i;
	int				num_of_bytes;

	va_start(ap, str);
	i = 0;
	num_of_bytes = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			handle_c_to_p(ap, str, &i, &num_of_bytes);
			handle_d_to_u(ap, str, &i, &num_of_bytes);
			handle_x_to_per(ap, str, &i, &num_of_bytes);
			i++;
		}
		else
			num_of_bytes += 1 * write(1, &str[i], 1);
		if (num_of_bytes < 0)
			return (num_of_bytes);
		i++;
	}
	va_end(ap);
	return (num_of_bytes);
}
