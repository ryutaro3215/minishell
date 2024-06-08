#include "../include/builtin.h"

void	*find_shell_builtin(char *command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (&builtin_echo);
	else if (ft_strcmp(command, "cd") == 0)
		return (&builtin_cd);
	else if (ft_strcmp(command, "pwd") == 0)
		return (&builtin_pwd);
	else if (ft_strcmp(command, "export") == 0)
		return (&builtin_export);
	else if (ft_strcmp(command, "unset") == 0)
		return (&builtin_unset);
	else if (ft_strcmp(command, "env") == 0)
		return (&builtin_env);
	else if (ft_strcmp(command, "exit") == 0)
		return (&builtin_env);
	else
		return (NULL);
}
