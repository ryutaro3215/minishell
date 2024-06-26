/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:23 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:24 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>

# include "environ.h"
# include "free.h"
# include "error.h"
# include "libft.h"

# define UPDATE 1 // when change PWD or OLDPWD environment variable.
# define NO_UPDATE 0

// init.c
void	shell_initialize(void);
char	**initialize_environ(void);

// init_utils.c
int		get_shell_level(void);
void	init_shell_level(void);
void	init_shell_underscore(void);
void	init_shell_pwd(int update_flag);
void	init_shell_oldpwd(int update_flag);

#endif
