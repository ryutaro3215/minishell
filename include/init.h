#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <signal.h>

#include "environ.h"
#include "free.h"
#include "libft.h"

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
