#include "../include_bonus/eval_bonus.h"

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
	else // parse error
		last_command_exit_status = EXECUTION_FAILURE;
	return (last_command_exit_status);
}
