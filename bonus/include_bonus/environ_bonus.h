/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:00 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:01 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRON_BONUS_H
# define ENVIRON_BONUS_H

# include "free_bonus.h"
# include "error_bonus.h"
# include "libft_bonus.h"
# include "xmalloc_bonus.h"

# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define EXPORT 1
# define UNSET 2

// environ.c
void	unset_environ_var(char *ignored_var);
void	replace_environ_var(char *new_environ_var);
void	add_environ_var(char *new_environ_var);

// environ_utils.c
size_t	count_strs(char **strs);
size_t	count_environ_var(void);
char	*get_environ_value(char *environ_var);
char	*get_environ_name(char *environ_var);
bool	environ_already_exist(char *new_environ_var, int flag);

#endif
