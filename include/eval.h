#ifndef EVAL_H
# define EVAL_H

# include "parse.h"
# include "exec.h"

# include <readline/history.h>

# define PARSE_ERROR 2

int	eval(char *line, int last_command_exit_status);

#endif
