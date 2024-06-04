#include "include/minishell.h"

extern sig_atomic_t	g_interrupt_state;

void	shell_initialize(void)
{
	extern char	**environ;

	signal(SIGQUIT, SIG_IGN);
	environ = initialize_environ();
}

t_command	*eval_command(char *line)
{
	t_token	*token_list;
	t_command	*command_list;

	token_list = tokenize(line);
	command_list = parse(token_list);
	if (!command_list)
		return NULL;
	if (need_here_document(token_list))
		gather_here_document(command_list);
	free_token_list(token_list);
	return command_list;
}

int	reader_loop(void)
{
	char		*line;
	t_command	*command_list = NULL;
	int			EOF_reached = 0;
	int			last_command_exit_status = 0;

	while (EOF_reached == 0)
	{
		signal(SIGINT, sigint_handler_for_readline);
		line = readline("minishell $ ");
		if (!line)
		{
			EOF_reached = EOF;
			continue;
		}
		signal(SIGINT, sigint_handler_for_exec);
		last_command_exit_status = sigint_is_traped(last_command_exit_status);
		printf("last_command_exit_status: %d\n", last_command_exit_status);
		if (*line)
		{
			add_history(line);
			command_list = eval_command(line);
			// expand(command_list);
			if (command_list)
			{
				last_command_exit_status = execute_command(command_list);
				free_command_list(command_list);
			}
			else // parse error
				last_command_exit_status = EXECUTION_FAILURE;
		}
		else
			last_command_exit_status = EXECUTION_SUCCESS;
		free(line);
	}
	// when Ctrl + C is pushed, the exit status is ...
	free_argv(environ);
	printf("exit\n");
	return (last_command_exit_status);
}

int	main()
{
	int	last_command_exit_status;

	shell_initialize();
	last_command_exit_status = reader_loop();
	return (last_command_exit_status);
}
