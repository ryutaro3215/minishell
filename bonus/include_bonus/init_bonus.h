#ifndef INIT_BONUS_H
# define INIT_BONUS_H


# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <limits.h>

# include "environ_bonus.h"
# include "free_bonus.h"
# include "error_bonus.h"
# include "libft_bonus.h"

# define UPDATE 1 // when change PWD or OLDPWD environment variable.
# define NO_UPDATE 0

// init.c
void	shell_initialize(void);
char	**initialize_environ(void);

// init_utils.c
int		get_shell_level(void);
void	init_shell_level(void);
void	init_shell_underscore(void);
void	init_shell_pwd(int update_flag);
void	init_shell_oldpwd(int update_flag);

#endif
