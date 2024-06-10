#include "../include_bonus/exec_bonus.h"

char	*create_path(char *path_vars, size_t path_var_len, char *line)
{
	char	*path_var;

	path_var = ft_strndup(path_vars, path_var_len);
	path_var = strjoin_but_freed_only_first_arg(path_var, "/\0");
	path_var = strjoin_but_freed_only_first_arg(path_var, line);
	return (path_var);
}

bool	have_right_permission(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) < 0)
	{
		ft_err_printf("minishell: %s: No such file or directory\n", path);
		exit(COMMAND_NOT_FOUND);
	}
	if (S_ISDIR(buf.st_mode))
	{
		ft_err_printf("minishell: %s: Is a directory\n", path);
		exit(NO_PERMISSION);
	}
	if (access(path, X_OK) < 0)
	{
		ft_err_printf("minishell: %s: Permission denied\n", path);
		exit(NO_PERMISSION);
	}
	return (true);
}

char	*get_path(char *line)
{
	size_t	path_var_len;
	char	*path;
	char	*path_vars;
	char	*end;

	if (ft_strchr(line, '/') && have_right_permission(line))
		return (line);
	path_vars = getenv("PATH");
	while (1)
	{
		if (*path_vars == ':')
			path_vars++;
		end = ft_strchr(path_vars, ':');
		if (!end)
			path_var_len = ft_strlen(path_vars);
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
	argv = xmalloc(sizeof(char *) * (count + 1));
	while (i < count)
	{
		argv[i] = token_list->name;
		i++;
		token_list = token_list->next;
	}
	argv[i] = NULL;
	return (argv);
}
