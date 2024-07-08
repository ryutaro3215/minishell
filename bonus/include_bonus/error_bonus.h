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
void	ft_err_printf(const char *str, char *var);

#endif
