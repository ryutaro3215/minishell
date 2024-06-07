#include "../include/environ.h"

size_t	count_strs(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i])
		i++;
	return i;
}

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

