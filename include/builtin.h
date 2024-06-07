#ifndef BUILTIN_H
#define BUILTIN_H

#include "parse.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>

// each builtin files
int		builtin_echo(t_token *word_list);
int		builtin_cd(t_token *word_list);
int		builtin_pwd(t_token *word_list);
int		builtin_export(t_token *word_list);
int		builtin_unset(t_token *word_list);
int		builtin_env(t_token *word_list);
int		builtin_exit(int last_command_exit_status);

// builtin_utils.c
void	*find_shell_builtin(char *command);

#endif
