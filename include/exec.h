#ifndef EXEC_H
#define EXEC_H

#include "init.h"
#include "env.h"
#include "parse.h"
#include "free.h"
#include "libft.h"

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

#define UPDATE 1 // when change PWD or OLDPWD environment variable.
#define NO_UPDATE 0

#define NO_PIPE -1

extern char	**environ;

// exec.c
int	execute_builtin(t_simple *simple, int (*builtin)(t_token *));
int	execute_disk_command(char *path, char **argv);
int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out, int (*builtin)(t_token *));
int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out, int last_command_exit_status);
int	execute_pipeline(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status);
int	execute_connection(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status);
int	execute_command_internal(t_command *command, int pipe_in, int pipe_out, int last_command_exit_status);
int	execute_command(t_command *command, int last_command_exit_status);

// exec_utils.c
char	*create_path(char *path_vars, size_t path_var_len, char *line);
char	*get_path(char *line);
char	**get_argv(t_token *token_list);

// redirect.c
int	do_r_input(char *filename);
int	do_r_output(char *filename);
int	do_r_append_output(char *filename);
int	do_redirect(t_redirect *redirect_list);

// builtin.c
void	*find_shell_builtin(char *command);
int		builtin_echo(t_token *word_list);
int		builtin_cd(t_token *word_list);
int		builtin_pwd(t_token *word_list);
int		builtin_export(t_token *word_list);
int		builtin_unset(t_token *word_list);
int		builtin_env(t_token *word_list);
int		builtin_exit(t_token *word_list);

// expand.c
t_token	*delete_current_word(t_simple *simple, t_token *current_word);
char	*get_env_value(char *env_name);
char	*get_env_name(char *word);
char	*get_last_single_quote(char *word);
void	expand_words(t_simple *simple, int last_command_exit_status);
char	*append_char(char *word, char c);


#endif
