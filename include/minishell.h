#ifndef MINISHELL_H
#define MINISHELL_H

#include "init.h"
#include "signal.h"
#include "env.h"
#include "eval.h"
#include "parse.h"
#include "exec.h"
#include "free.h"

#include <readline/readline.h>
#include <readline/history.h>

int			reader_loop(int *EOF_reached, int last_command_exit_status);

#endif
