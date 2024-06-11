#ifndef FREE_BONUS_H
# define FREE_BONUS_H

# include "minishell_bonus.h"

# include <stdlib.h>

void	free_token_list(t_token *token_list);
void	free_redirect_list(t_redirect *redirect_list);
void	free_simple(t_command *command);
void	free_command_list(t_command *command_list);
void	free_2d_array(char **array);

#endif
