#ifndef MINISHELL_H
#define MINISHELL_H

#include "init.h"
#include "signal.h"
#include "env.h"
#include "parse.h"
#include "exec.h"
#include "free.h"

#include <readline/readline.h>
#include <readline/history.h>

t_command	*eval_command(char *line);
int			reader_loop(void);

#endif
