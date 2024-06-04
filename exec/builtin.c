#include "../include/exec.h"

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
/*
int	builtin_export(t_token *word_list)
{
	extern char	**environ;

	(void)word_list;
}
*/
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
