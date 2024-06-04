#ifndef SIGNAL_H
#define SIGNAL_H

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>


void	sigint_handler_for_readline(int sig);
void	sigint_handler_for_exec(int sig);
int		sigint_is_traped(int last_command_exit_status);

#endif
