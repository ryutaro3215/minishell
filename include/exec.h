#ifndef EXEC_H
#define EXEC_H

#include "tokenize.h"
#include "parse.h"
#include "free.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define EXECUTION_FAILURE 1

#define NO_PIPE -1

// exec.c
//int	execute_builtin(t_simple *simple, func *builtin);
int	execute_disk_command(char *path, char **argv);
int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out); //, func *builtin)
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

#endif
