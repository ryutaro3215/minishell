#include "../include/env.h"

size_t	count_environ_var(void)
{
	extern char	**environ;
	char		**tmp;
	size_t		i;

	tmp = environ;
	i = 0;
	while (tmp[i])
		i++;
	return i;
}

char	*get_environ_value(char *environ_var)
{
	char	*environ_value;

	environ_value = strchr(environ_var, '=') + 1;
	if (*environ_value == '\0')
		return NULL;
	return (strdup(environ_value));
}

char	*get_environ_name(char *environ_var)
{
	char	*end;

	end = strchr(environ_var, '=');
	return (strndup(environ_var, end - environ_var));
}

bool	environ_already_exist(char *new_environ_var, int flag)
{
	char		*new_environ_name;
	char		*old_environ_name;
	extern char	**environ;
	char		**tmp;
	size_t		i;

	if (flag == EXPORT)
		new_environ_name = get_environ_name(new_environ_var);
	else // flag == UNSET
		new_environ_name = strdup(new_environ_var);
	tmp = environ;
	i = 0;
	while (tmp[i])
	{
		old_environ_name = get_environ_name(tmp[i]);
		if (strcmp(new_environ_name, old_environ_name) == 0)
		{
			free(new_environ_name);
			free(old_environ_name);
			return true;
		}
		free(old_environ_name);
		i++;
	}
	free(new_environ_name);
	return false;
}

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
		new_environ[i] = strdup(tmp[j]);
		i++;
		j++;
	}
	new_environ[i] = NULL;
	free_argv(environ);
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
	free_argv(environ);
	environ = new_environ;
}

static size_t	count_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return i;
}

char	**initialize_environ(void)
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
		//printf("current environ: %p\n", my_environ[i]);
		//printf("%s\n", my_environ[i]);
		i++;
	}
	my_environ[i] = NULL;
	return my_environ;
}
