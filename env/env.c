#include "../include/env.h"

size_t	count_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return i;
}

char	**initialize_environ()
{
	extern char	**environ;
	char		**my_environ;
	size_t		i;

	if (!environ) // ?
		return NULL;
	my_environ = malloc(sizeof(char *) * (count_strs(environ) + 1));
	i = 0;
	while (environ[i])
	{
		my_environ[i] = strdup(environ[i]);
		i++;
	}
	my_environ[i] = NULL;
	return my_environ;
}
