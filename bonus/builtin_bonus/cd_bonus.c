#include "../include_bonus/builtin_bonus.h"

static size_t	count_words(t_token *word_list)
{
	size_t	count;

	count = 0;
	while (word_list)
	{
		count++;
		word_list = word_list->next;
	}
	return (count);
}

int	builtin_cd(t_token *word_list)
{
	size_t	count;

	count = count_words(word_list);
	if (count > 2)
	{
		ft_err_printf("minishell: cd: Too many arguments\n");
		return (EXECUTION_FAILURE);
	}
	if (!word_list->next)
		return (EXECUTION_SUCCESS);
	init_shell_oldpwd(UPDATE);
	if (chdir(word_list->next->name) < 0)
	{
		perror("minishell: cd");
		return (EXECUTION_FAILURE);
	}
	init_shell_pwd(UPDATE);
	return (EXECUTION_SUCCESS);
}
