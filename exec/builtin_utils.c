#include "../include/builtin.h"

int	retrieve_fdin_fdout(int fdin, int fdout)
{
	if (dup2(fdin, 0) < 0 || dup2(fdout, 1) < 0)
	{
		close(fdin);
		close(fdout);
		ft_err_printf("dup error\n");
		return (-1);
	}
	return (0);
}

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
