#include "../include/free.h"

void	free_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->name);
		free(token_list);
		token_list = tmp;
	}
}

void	free_redirect_list(t_redirect *redirect_list)
{
	t_redirect	*tmp;

	while (redirect_list)
	{
		tmp = redirect_list->next;
		free(redirect_list->filename);
		free(redirect_list);
		redirect_list = tmp;
	}
}

void	free_simple(t_command *command)
{
	free_token_list(command->value.simple->word_list);
	free_redirect_list(command->value.simple->redirect_list);
	free(command->value.simple);
	free(command);
}

void	free_command_list(t_command *command_list)
{
	if (command_list->attribute == cm_simple)
		free_simple(command_list);
	else // command_list->attribute == cm_connection
	{
		free_command_list(command_list->value.connection->first);
		free_command_list(command_list->value.connection->second);
		free(command_list->value.connection);
		free(command_list);
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}