#ifndef ENV_H
#define ENV_H

#include "free.h"

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define EXPORT 1
#define UNSET 2

size_t	count_environ_var(void);
char	*get_environ_value(char *environ_var);
char	*get_environ_name(char *environ_var);
bool	environ_already_exist(char *new_environ_var, int flag);
void	unset_environ_var(char *ignored_var);
void	replace_environ_var(char *new_environ_var);
void	add_environ_var(char *new_environ_var);
char	**initialize_environ(void);

#endif
