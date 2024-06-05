#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <signal.h>

#include "env.h"

int		get_shell_level();
void	init_shell_level(void);
void	shell_initialize(void);

#endif
