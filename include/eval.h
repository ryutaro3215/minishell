#ifndef EVAL_H
#define EVAL_H

#include "../include/parse.h"
#include "../include/exec.h"

#include <readline/history.h>

int	eval(char *line, int last_command_exit_status);

#endif
