t_command	*read_command(void)
{
	line = readline("minishell $ ");
	token_list = tokenize(line);
	command_list = parse(token_list);
	if (need_here_documents) // ?
		gather_here_documents();
	return command_list;
}

int	execute_builtin(t_simple *simple, func *builtin)
{
	
}

int	execute_in_subshell(t_simple *simple, func *builtin)
{
	static int	fdin;
	static int	fdout;
	int			fildes[2];

	pipe(fildes);
	if (builtin)
	{
		// execute builtin in child process.
	}
	else
	{
		// execute disk command in child process.
	}
}

int	execute_simple_command(t_simple *simple)
{
	func	*builtin = find_shell_builtin(simple); // return function pointer
	if (builtin && !simple->subshell)
		return (execute_builtin(simple, builtin));
	return (execute_in_subshell(simple, builtin)); // and separate in this function (one for builtin, another for disk command)
/* or
	if (builtin)
	{
		if (builtin && subshell)
			execute_subshell_builtin(builtin); // pass pipe_in and pipe_out
		else // builtin && !subshell
			execute_builtin(builtin); // don't pass pipe_in and pipe_out
	}
	else // not builtin
		execute_disk_command(); // pass pipe_in and pipe_out
*/
}

int	execute_pipeline(t_command *command)
{
	execute_command(command->value.Connection->first);
	return (execute_command(command->value.Connection->second));
}

int	execute_connection(t_command *command)
{
//	int	connector = command->value.connection->connector;

	// if (connector == pipe)
	return (execute_pipeline(command));
	// else if (connector == ...) you can add '&&' '||' '&'
}

int	execute_command(t_command *command)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->value.simple, NO_PIPE, NO_PIPE));
	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		return (execute_connection(command));
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
		// expand(last_command_exit_status);
		if (command_list)
			last_command_exit_status = execute_command(command_list);
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
