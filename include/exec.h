#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"
# include "init.h"
# include "environ.h"
# include "parse.h"
# include "free.h"
# include "builtin.h"
# include "expand.h"
# include "libft.h"
# include "error.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/wait.h>

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
pid_t	do_fork(void);
int		do_pipe(int pipe_in, int pipe_out);
char	*create_path(char *path_vars, size_t path_var_len, char *line);
char	*get_path(char *line);
char	**get_argv(t_token *token_list);

// redirect.c
int		do_r_input(char *filename);
int		do_r_output(char *filename);
int		do_r_append_output(char *filename);
int		do_redirect(t_redirect *redirect_list);

#endif
