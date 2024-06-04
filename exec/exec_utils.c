#include "../include/exec.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*create_path(char *path_vars, size_t path_var_len, char *line)
{
	char	*path_var;

	path_var = strndup(path_vars, path_var_len);
	path_var = ft_strjoin(path_var, "/\0");
	path_var = ft_strjoin(path_var, line);
	return path_var;
}

char	*get_path(char *line)
{
	size_t	path_var_len;
	char	*path;
	char	*path_vars;
	char	*end;

	if (strchr(line, '/'))
	{
		if (access(line, X_OK) >= 0)
			return (strdup(line));
		return NULL;
	}
	path_vars = getenv("PATH");
	while (1)
	{
		if (*path_vars == ':')
			path_vars++;
		end = strchr(path_vars, ':');
		if (!end)
			path_var_len = strlen(path_vars);
		else
;			path_var_len = end - path_vars;
		path = create_path(path_vars, path_var_len, line);
		if (access(path, X_OK) >= 0)
			return path;
		free(path);
		if (!end)
			break;
		path_vars += path_var_len;
	}
	return NULL;
}

char	**get_argv(t_token *token_list)
{
	int		count = 1;
	t_token	*tmp;
	char	**argv;
	int		i = 0;

	tmp = token_list;
	while (tmp->next)
	{
		tmp = tmp->next;
		count++;
	}
	argv = malloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		argv[i] = token_list->name;
		i++;
		token_list = token_list->next;
	}
	argv[i] = NULL;
	return argv;
}

void	*find_shell_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (&builtin_echo);
	else if (strcmp(command, "pwd") == 0)
		return (&builtin_pwd);
	else if (strcmp(command, "export") == 0)
		return (&builtin_export);
	else if (strcmp(command, "env") == 0)
		return (&builtin_env);
	else if (strcmp(command, "exit") == 0)
		return (&builtin_exit);
	else
		return NULL;
}
