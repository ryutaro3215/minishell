#include "../include_bonus/eval_bonus.h"

extern sig_atomic_t	g_interrupt_state;

int	eval(char *line, int last_command_exit_status)
{
	t_command	*command_list;

	command_list = NULL;
	add_history(line);
	command_list = parse_command(line);
	if (command_list)
	{
		last_command_exit_status = execute_command(command_list,
				last_command_exit_status);
		free_command_list(command_list);
	}
	else if (g_interrupt_state)
	{
		last_command_exit_status = 128 + SIGINT;
		g_interrupt_state = 0;
	}
	else
		last_command_exit_status = PARSE_ERROR;
	return (last_command_exit_status);
}
