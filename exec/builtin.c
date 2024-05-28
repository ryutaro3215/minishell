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
