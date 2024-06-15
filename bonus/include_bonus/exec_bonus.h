/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:08 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:09 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

# include "minishell_bonus.h"
# include "init_bonus.h"
# include "environ_bonus.h"
# include "parse_bonus.h"
# include "free_bonus.h"
# include "builtin_bonus.h"
# include "expand_bonus.h"
# include "libft_bonus.h"
# include "error_bonus.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define EXECUTION_SUCCESS 0

# define EXECUTION_FAILURE 1

# define NO_PERMISSION 126
# define COMMAND_NOT_FOUND 127

# define NO_PIPE -1

// exec.c
int		execute_command_internal(t_command *command, int pipe_in, int pipe_out,
			int last_command_exit_status);
int		execute_command(t_command *command, int last_command_exit_status);

// exec_simple.c
int		execute_builtin(t_simple *simple, int (*builtin)(t_token *));
int		execute_disk_command(char *path, char **argv);
int		execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out,
			int (*builtin)(t_token *));
int		execute_simple_command(t_simple *simple, int pipe_in, int pipe_out,
			int last_command_exit_status);

// exec_connection.c
int		execute_pipeline(t_command *command, int pipe_in, int pipe_out,
			int last_command_exit_status);
int		execute_connection(t_command *command, int pipe_in, int pipe_out,
			int last_command_exit_status);

// exec_exit.c
int		execute_exit_builtin(t_simple *simple, int last_command_exit_status);
int		execute_exit_in_subshell(t_simple *simple, int pipe_in, int pipe_out,
			int last_command_exit_status);

// exec_null.c
int		execute_null_command(t_redirect *redirect_list,
			int pipe_in, int pipe_out);

// exec_utils.c
char	*create_path(char *path_vars, size_t path_var_len, char *line);
bool	have_right_permission(char *path);
char	*get_path(char *line);
char	**get_argv(t_token *token_list);

// redirect.c
int		do_r_input(char *filename);
int		do_r_output(char *filename);
int		do_r_append_output(char *filename);
int		do_redirect(t_redirect *redirect_list);

// do_pipe_fork.c
pid_t	do_fork(void);
int		do_pipe(int pipe_in, int pipe_out);

#endif
