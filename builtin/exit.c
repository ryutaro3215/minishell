#include "../include/builtin.h"

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

int	builtin_exit(t_token *word_list, int last_command_exit_status)
{
	size_t	count;

	count = count_words(word_list);
	if (count > 2)
	{
		ft_err_printf("minishell: exit: Too many arguments\n");
		return (EXECUTION_FAILURE);
	}
	ft_err_printf("exit\n");
	if (!word_list->next)
		exit(last_command_exit_status);
	exit(ft_atoi(word_list->next->name));
}
