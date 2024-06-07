#include "../include/builtin.h"

int	builtin_exit(int last_command_exit_status)
{
	printf("exit\n");
	exit(last_command_exit_status);
}
