#include "../include/builtin.h"

int	builtin_echo(t_token *word_list)
{
	t_token	*current_word;
	int		n_option_flag;

	current_word = word_list->next;
	if (!current_word)
	{
		printf("\n");
		return (EXECUTION_SUCCESS);
	}
	n_option_flag = 0;
	if (strcmp(current_word->name, "-n") == 0)
	{
		n_option_flag = 1;
		current_word = current_word->next;
	}
	while (current_word)
	{
		printf("%s", current_word->name);
		current_word = current_word->next;
		if (current_word)
			printf(" ");
	}
	if (!n_option_flag)
		printf("\n");
	return (EXECUTION_SUCCESS);
}
