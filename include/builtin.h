/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:04 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:05 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"
# include "exec.h"
# include "libft.h"
# include "error.h"

# include <string.h>
# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>

// builtin_utils.c
int		retrieve_fdin_fdout(int fdin, int fdout);
void	*find_shell_builtin(char *command);

// each builtin files
int		builtin_echo(t_token *word_list);
int		builtin_cd(t_token *word_list);
int		builtin_pwd(t_token *word_list);
int		builtin_export(t_token *word_list);
int		builtin_unset(t_token *word_list);
int		builtin_env(t_token *word_list);
int		builtin_exit(t_token *word_list, int last_command_exit_status);

#endif
