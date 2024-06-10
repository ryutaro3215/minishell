#ifndef BUILTIN_BONUS_H
# define BUILTIN_BONUS_H

# include "minishell_bonus.h"
# include "exec_bonus.h"
# include "libft_bonus.h"
# include "error_bonus.h"

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
