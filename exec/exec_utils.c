#include "../include/exec.h"

int	do_pipe(int pipe_in, int pipe_out)
{
	int	fd;

	fd = 0;
	if (pipe_in != NO_PIPE)
	{
		fd = dup2(pipe_in, 0);
		if (fd < 0)
			return (fd);
		close(pipe_in); // need error check
	}
	if (pipe_out != NO_PIPE)
	{
		fd = dup2(pipe_out, 1);
		if (fd < 0)
			return (fd);
		close(pipe_out);
	}
	return (fd);
}

char	*create_path(char *path_vars, size_t path_var_len, char *line)
{
	char	*path_var;

	path_var = strndup(path_vars, path_var_len);
	path_var = strjoin_but_freed_only_first_arg(path_var, "/\0");
	path_var = strjoin_but_freed_only_first_arg(path_var, line);
	return (path_var);
}

char	*get_path(char *line)
{
	size_t	path_var_len;
	char	*path;
	char	*path_vars;
	char	*end;

	if (strchr(line, '/'))
		return (line);
	path_vars = getenv("PATH");
	while (1)
	{
		if (*path_vars == ':')
			path_vars++;
		end = strchr(path_vars, ':');
		if (!end)
			path_var_len = strlen(path_vars);
		else
			path_var_len = end - path_vars;
		path = create_path(path_vars, path_var_len, line);
		if (access(path, X_OK) >= 0)
			return (path);
		free(path);
		if (!end)
			return (line);
		path_vars += path_var_len;
	}
}

char	**get_argv(t_token *token_list)
{
	int		count;
	t_token	*tmp;
	char	**argv;
	int		i;

	count = 1;
	i = 0;
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
	return (argv);
}
