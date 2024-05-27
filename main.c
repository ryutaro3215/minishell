t_command	*read_command(void)
{
	line = readline("minishell $ ");
	token_list = tokenize(line);
	command_list = parse(token_list);
	if (need_here_documents) // ?
		gather_here_documents();
	return command_list;
}

int	execute_simple_command(s_simple *simple)
{
	if (builtin)
	{
		if (builtin && subshell)
			execute_subshell_builtin();
		else // builtin && !subshell
			execute_builtin();
	}
	else // not builtin
	{
		execute_disk_command();
	}
}

int	execute_pipeline(s_command *command)
{
	execute_command(command->value.Connection->first);
	execute_command(command->value.Connection->second);
}

int	execute_connection(s_command *command)
{
	int	last_command_exit_status;
	int	connector = command->value.connecton->connector;

	if (connector == pipe)
		last_command_exit_status = execute_pipeline(command);
	else // execute_connection error
		;
	return (last_command_exit_status);
}

int	execute_command(int last_command_exit_status, t_command *command)
{
	if (command->attribute == cm_simple) // just word list
		last_command_exit_status = execute_simple_command(command->value.simple, NO_PIPE, NO_PIPE);
	else if (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		last_command_exit_status = execute_connection(command);
	else // execute_command error
		;
	return (last_command_exit_status);

//	if (command->attribute == cm_subshell)
//		execute_subshell(command);
}

int	reader_loop(void)
{
	t_token		*token_list = NULL;
	t_command	*command_list = NULL;
	int			EOF_reached = 0;
	int			last_command_exit_status = 0;

	while (EOF_reached == 0)
	{
		command_list = read_command();
		if (command_list)
			last_command_exit_status = execute_command(last_command_exit_status, command_list);
		else // parse error
			EOF_reached = EOF;
	}
	return (last_command_exit_status);
}

int	main(int argc, char *argv[])
{
// configuration and initialization for shell script(uninteractive), oneshot command and interactive.
	signal_init();// ?

	int	last_command_exit_status = reader_loop();

	return (last_command_exit_status);
}
