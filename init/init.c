#include "../include/init.h"
#include "../include/free.h"

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
	return (s3);
}

static int	num_of_digit(long n)
{
	int	count;

	count = 0;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

static char	*when_minus(int *n_digit, int *c, long *__n)
{
	int		i;
	char	*str;

	*__n *= -1;
	*n_digit = num_of_digit(*__n);
	i = *n_digit;
	str = (char *)malloc((*n_digit + 1) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	while (1 <= i)
	{
		*c = *__n % 10;
		str[i] = *c + '0';
		*__n = *__n / 10;
		i--;
	}
	str[i] = '-';
	str[*n_digit + 1] = '\0';
	return (str);
}

static char	*when_plus(int *n_digit, int *c, long *__n)
{
	int		i;
	char	*str;

	*n_digit = num_of_digit(*__n);
	i = *n_digit - 1;
	str = (char *)malloc((*n_digit * sizeof(char) + 1));
	if (str == NULL)
		return (NULL);
	while (0 <= i)
	{
		*c = *__n % 10;
		str[i] = *c + '0';
		*__n = *__n / 10;
		i--;
	}
	str[*n_digit] = '\0';
	return (str);
}

static char	*ft_itoa(int n)
{
	int		n_digit;
	int		c;
	char	*str;
	long	__n;

	__n = n;
	if (__n < 0)
	{
		str = when_minus(&n_digit, &c, &__n);
		return (str);
	}
	else
	{
		str = when_plus(&n_digit, &c, &__n);
		return (str);
	}
}

int	get_shell_level()
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
			free(shlvl_name);
			free(new_shell_level);
			free(shlvl_var);
		}
	}
}

void	init_shell_underscore()
{
	char	buf[PATH_MAX + 1];
	char	underscore[PATH_MAX + 3];

	strlcat(getcwd(buf, PATH_MAX), "/./minishell", PATH_MAX + 1);
	underscore[0] = '_';
	underscore[1] = '=';
	underscore[2] = '\0';
	strlcat(underscore, buf, PATH_MAX + 3); // "_=\0" is three character.
	if (!environ_already_exist("_", UNSET))
		add_environ_var(underscore);
	else
		replace_environ_var(underscore);
}

void	shell_initialize(void)
{
	extern char	**environ;

	signal(SIGQUIT, SIG_IGN);
	environ = initialize_environ();
	init_shell_level();
	init_shell_underscore();
}

