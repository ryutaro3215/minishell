/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:10 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:11 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# include "libft.h"

// error.c
void	handle_error(bool is_error);

// ft_err_printf.c
void	ft_err_printf(const char *str, char *var);

#endif
