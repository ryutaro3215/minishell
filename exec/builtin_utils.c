#include "../include/builtin.h"

void	*find_shell_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (&builtin_echo);
	else if (strcmp(command, "cd") == 0)
		return (&builtin_cd);
	else if (strcmp(command, "pwd") == 0)
		return (&builtin_pwd);
	else if (strcmp(command, "export") == 0)
		return (&builtin_export);
	else if (strcmp(command, "unset") == 0)
		return (&builtin_unset);
	else if (strcmp(command, "env") == 0)
		return (&builtin_env);
	else if (strcmp(command, "exit") == 0)
		return (&builtin_env);
	else
		return NULL;
}
