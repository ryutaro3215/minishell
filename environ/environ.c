#include "../include/environ.h"

void	unset_environ_var(char *ignored_var)
{
	char		**new_environ;
	extern char	**environ;
	char		**tmp;
	char		*environ_name;
	size_t		i;
	size_t		j;

	new_environ = malloc(sizeof(char *) * ((count_environ_var() - 1) + 1)); // delete one element
	tmp = environ;
	i = 0;
	j = 0;
	while (tmp[j])
	{
		environ_name = get_environ_name(tmp[j]);
		if (strcmp(environ_name, ignored_var) == 0)
		{
			j++;
			free(environ_name);
			continue;
		}
		free(environ_name);
		new_environ[i++] = strdup(tmp[j++]);
	}
	new_environ[i] = NULL;
	free_2d_array(environ);
	environ = new_environ;
}

void	replace_environ_var(char *new_environ_var)
{
	extern char	**environ;
	char		**tmp;
	size_t		i;
	char		*new_environ_name;
	char		*old_environ_name;

	new_environ_name = get_environ_name(new_environ_var);
	tmp = environ;
	i = 0;
	while (tmp[i])
	{
		old_environ_name = get_environ_name(tmp[i]);
		if (strcmp(new_environ_name, old_environ_name) == 0)
		{
			free(tmp[i]);
			tmp[i] = strdup(new_environ_var);
			free(new_environ_name);
			free(old_environ_name);
			return;
		}
		free(old_environ_name);
		i++;
	}
	free(new_environ_name);
}

void	add_environ_var(char *new_environ_var)
{
	char		**new_environ;
	char		**old_environ;
	extern char	**environ;
	size_t		i;

	// new_environ_var + nullptr = 2
	new_environ = malloc(sizeof(char *) * (count_environ_var() + 2));
	old_environ = environ;
	i = 0;
	while (old_environ[i])
	{
		new_environ[i] = strdup(old_environ[i]);
		i++;
	}
	new_environ[i++] = strdup(new_environ_var);
	new_environ[i] = NULL;
	free_2d_array(environ);
	environ = new_environ;
}
