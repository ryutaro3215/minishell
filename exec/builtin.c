#include "../include/exec.h"

size_t	count_environ_var()
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

void	add_environ_var(char *new_environ_var)
{
	char		**new_environ;
	char		**old_environ;
	extern char	**environ;
	size_t		i;

	new_environ = malloc(sizeof(char *) * (count_environ_var() + 2));
	// new_environ_var + nullptr = 2
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

int	builtin_echo(t_token *word_list)
{
	t_token	*current_word;

	current_word = word_list->next;
	while (current_word)
	{
		printf("%s", current_word->name);
		current_word = current_word->next;
		if (current_word)
			printf(" ");
	}
	printf("\n");
	return EXECUTION_SUCCESS;
}

int	builtin_pwd(t_token *word_list)
{
	char	buf[PATH_MAX];

	(void)word_list;
	printf("%s\n", getcwd(buf, PATH_MAX));
	return EXECUTION_SUCCESS;
}

int	builtin_export(t_token *word_list)
{
	t_token		*current_token;

	current_token = word_list->next;
	while (current_token)
	{
		add_environ_var(current_token->name);
		current_token = current_token->next;
	}
	return EXECUTION_SUCCESS;
}

int	builtin_env(t_token *word_list)
{
	extern char	**environ;
	char	**tmp;
	(void)word_list;

	tmp = environ;
	if (tmp)
	{
		while (*tmp)
		{
			printf("%s\n", *tmp);
			tmp++;
		}
	}
	return EXECUTION_SUCCESS;
}

int	builtin_exit(t_token *word_list)
{
	(void)word_list;
	printf("exit\n");
	exit(EXECUTION_SUCCESS);
}
