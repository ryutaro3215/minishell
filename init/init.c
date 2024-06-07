#include "../include/init.h"

char	**initialize_environ(void)
{
	extern char	**environ;
	char		**my_environ;
	size_t		i;

	if (!environ) // ?
		return (NULL);
	my_environ = malloc(sizeof(char *) * (count_strs(environ) + 1));
	i = 0;
	while (environ[i])
	{
		my_environ[i] = strdup(environ[i]);
		i++;
	}
	my_environ[i] = NULL;
	return (my_environ);
}

void	shell_initialize(void)
{
	extern char	**environ;

	signal(SIGQUIT, SIG_IGN);
	environ = initialize_environ();
	init_shell_level();
	init_shell_underscore();
	init_shell_pwd(NO_UPDATE);
	init_shell_oldpwd(NO_UPDATE);
}
