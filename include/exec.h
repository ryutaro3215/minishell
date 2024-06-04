#ifndef EXEC_H
#define EXEC_H

#include "parse.h"
#include "free.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/wait.h>

#define EXECUTION_SUCCESS 0
#define EXECUTION_FAILURE 1
#define COMMAND_NOT_FOUND 127

#define NO_PIPE -1

extern char	**environ;

// exec.c
int	execute_builtin(t_token *word_list, int (*builtin)(t_token *));
int	execute_disk_command(char *path, char **argv);
int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out, int (*builtin)(t_token *));
int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out);
int	execute_pipeline(t_command *command, int pipe_in, int pipe_out);
int	execute_connection(t_command *command, int pipe_in, int pipe_out);
int	execute_command_internal(t_command *command, int pipe_in, int pipe_out);
int	execute_command(t_command *command);

// exec_utils.c
char	*ft_strjoin(char *s1, char *s2);
char	*create_path(char *path_vars, size_t path_var_len, char *line);
char	*get_path(char *line);
char	**get_argv(t_token *token_list);
void	*find_shell_builtin(char *command);

// redirect.c
int	do_r_input(char *filename);
int	do_r_output(char *filename);
int	do_r_append_output(char *filename);
int	do_redirect(t_redirect *redirect_list);

// builtin.c
int	builtin_echo(t_token *word_list);
int	builtin_pwd(t_token *word_list);
int	builtin_env(t_token *word_list);
int	builtin_exit(t_token *word_list);

#endif
