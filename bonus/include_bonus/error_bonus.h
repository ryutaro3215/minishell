/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:03 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:04 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_BONUS_H
# define ERROR_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# include "libft_bonus.h"

// error.c
void	handle_error(bool is_error);

// ft_err_printf.c
int		ft_err_printf(const char *str, ...);
int		err_if_char(va_list ap);
int		err_if_char_p(va_list ap);
int		err_if_void_p(va_list ap);
int		err_if_decimal(va_list ap);
int		err_if_unsigned_decimal(va_list ap);
int		err_if_hexadec_low(va_list ap);
int		err_if_hexadec_up(va_list ap);
int		ft_err_put_int(int n, int *p);
int		ft_err_put_unsigned_int(unsigned int n, int *p);
int		ft_err_put_address(uintptr_t n, int *p);
int		ft_err_put_hexadec_low(unsigned int n, int *p);
int		ft_err_put_hexadec_up(unsigned int n, int *p);

#endif
