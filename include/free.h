#ifndef FREE_H
#define FREE_H

#include "parse.h"

#include <stdlib.h>

void	free_token_list(t_token *token_list);
void	free_redirect_list(t_redirect *redirect_list);
void	free_simple(t_command *command);
void	free_command_list(t_command *command_list);
void	free_argv(char **argv);

#endif
