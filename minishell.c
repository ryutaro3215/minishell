#include "include/minishell.h"

t_command	*eval_command(char *line)
{
	t_token	*token_list;
	t_command	*command_list;

	token_list = tokenize(line);
	command_list = parse(token_list);
	free_token_list(token_list);
//	if (need_here_documents) // ?
//		gather_here_documents();
	return command_list;
}

int	reader_loop(void)
{
	char		*line;
	t_command	*command_list = NULL;
//	int			EOF_reached = 0;
	int			last_command_exit_status = 0;

	while (1) // EOF_reached == 0)
	{
		line = readline("minishell $ ");
		if (!line)
			break;
		if (*line)
		{
			add_history(line);
			command_list = eval_command(line);
			free(line);
			// expand(last_command_exit_status);
			if (command_list)
			{
				last_command_exit_status = execute_command(command_list);
				free_command_list(command_list);
			}
			else // parse error
				last_command_exit_status = EXECUTION_FAILURE;
			printf("exit_status: %d\n", last_command_exit_status);
		}
	}
	// when Ctrl + C is pushed, the exit status is ...
	return (last_command_exit_status);
}

int	main()
{
// configuration and initialization for shell script(uninteractive), oneshot command and interactive.
	signal_init();// ?

	int	last_command_exit_status = reader_loop();

	return (last_command_exit_status);
}

/*
__attribute__((destructor))
static void	destructor()
{
	system("leaks -q a.out");
}
*/
