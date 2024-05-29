#ifndef MINISHELL_H
#define MINISHELL_H

#include "signal.h"
#include "parse.h"
#include "exec.h"
#include "free.h"

#include <readline/readline.h>
#include <readline/history.h>

volatile sig_atomic_t	interrupt_state = 0; // non-zero after SIGINT

t_command	*eval_command(char *line);
int			reader_loop(void);

#endif
