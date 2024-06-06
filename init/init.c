#include "../include/init.h"

int	get_shell_level(void)
{
	extern char	**environ;
	char		**tmp;
	size_t		i;
	char		*environ_name;
	char		*environ_value;

	tmp = environ;
	i = 0;
	while (tmp[i])
	{
		environ_name = get_environ_name(tmp[i]);
		if (strcmp(environ_name, "SHLVL") == 0)
		{
			environ_value = strchr(tmp[i], '=') + 1; // when environ_value = NULL ?
			free(environ_name);
			return (atoi(environ_value));
		}
		free(environ_name);
		i++;
	}
	return (0);
}

void	init_shell_level(void)
{
	int			current_shell_level;
	char		*new_shell_level;
	char		*shlvl_name;
	char		*shlvl_var;

	if (!environ_already_exist("SHLVL", UNSET)) // UNSET means directly compare the word and each environ elements.
		add_environ_var("SHLVL=1");
	else
	{
		current_shell_level = get_shell_level();
		if (current_shell_level == 0) // when "SHLVL=" or some invalid number
			replace_environ_var("SHLVL=1");
		else
		{
			shlvl_name = strdup("SHLVL=");
			new_shell_level = ft_itoa(++current_shell_level);
			shlvl_var = ft_strjoin(shlvl_name, new_shell_level);
			replace_environ_var(shlvl_var);
			//free(shlvl_name);
			//free(new_shell_level);
			free(shlvl_var);
		}
	}
}

void	init_shell_underscore(void)
{
	char	buf[PATH_MAX + 1];
	char	underscore[PATH_MAX + 3];

	if (!environ_already_exist("_", UNSET))
	{
		strlcat(getcwd(buf, PATH_MAX), "/./minishell", PATH_MAX + 1);
		underscore[0] = '_';
		underscore[1] = '=';
		underscore[2] = '\0';
		strlcat(underscore, buf, PATH_MAX + 3); // "_=\0" is three character.
		add_environ_var(underscore);
	}
}

void	init_shell_pwd(int update_flag)
{
	char	buf[PATH_MAX + 1];
	char	pwd[PATH_MAX + 5];

	if (!environ_already_exist("PWD", UNSET) || update_flag)
	{
		pwd[0] = 'P';
		pwd[1] = 'W';
		pwd[2] = 'D';
		pwd[3] = '=';
		pwd[4] = '\0';
		strlcat(pwd, getcwd(buf, PATH_MAX), PATH_MAX + 5);
		if (update_flag)
			replace_environ_var(pwd);
		else
			add_environ_var(pwd);
	}
}

void	init_shell_oldpwd(int update_flag)
{
	char	buf[PATH_MAX + 1];
	char	oldpwd[PATH_MAX + 8];

	if (!environ_already_exist("OLDPWD", UNSET) || update_flag)
	{
		oldpwd[0] = 'O';
		oldpwd[1] = 'L';
		oldpwd[2] = 'D';
		oldpwd[3] = 'P';
		oldpwd[4] = 'W';
		oldpwd[5] = 'D';
		oldpwd[6] = '=';
		oldpwd[7] = '\0';
		strlcat(oldpwd, getcwd(buf, PATH_MAX), PATH_MAX + 8);
		if (update_flag)
			replace_environ_var(oldpwd);
		else
			add_environ_var(oldpwd);
	}
}

void	shell_initialize(void)
{
	extern char	**environ;

	signal(SIGQUIT, SIG_IGN);
	environ = initialize_environ();
	init_shell_level();
	init_shell_underscore();
	init_shell_pwd(NO_UPDATE); // not update flag
	init_shell_oldpwd(NO_UPDATE); // not update flag
}
