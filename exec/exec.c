#include "../include/exec.h"

/*
int	execute_builtin(t_simple *simple, func *builtin)
{
	
}
*/


int	execute_disk_command(char *path, char **argv)
{
	execve(path, argv, NULL);
	printf("internal error: execution\n");
	return (EXECUTION_FAILURE);
}

int	execute_in_subshell(t_simple *simple) //, func *builtin)
{
//	static int	fdin;
//	static int	fdout;
//	int			fildes[2];
	pid_t	pid;
	char	*path;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
//	if (pipe(fildes) < 0)
//		return (EXECUTION_FAILURE);
	path = get_path(simple->word_list->name);
	argv = get_argv(simple->word_list);
//	if (builtin)
//	{
		// execute builtin in child process.
//	}
//	else
//	{
		// execute disk command in child process.
		if (pid == 0)
			exit(execute_disk_command(path, argv));
		free(path);
		free_argv(argv);
		return (wait(NULL));
//	}
}

int	execute_simple_command(t_simple *simple)
{
//	func	*builtin = find_shell_builtin(simple); // return function pointer
//	if (builtin && !simple->subshell)
//		return (execute_builtin(simple, builtin));
	return (execute_in_subshell(simple)); //, builtin)); // and separate in this function (one for builtin, another for disk command)
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

/*
int	execute_pipeline(t_command *command)
{
	execute_command(command->value.Connection->first);
	return (execute_command(command->value.Connection->second));
}
*/

/*
int	execute_connection(t_command *command)
{
//	int	connector = command->value.connection->connector;

	// if (connector == pipe)
	return (execute_pipeline(command));
	// else if (connector == ...) you can add '&&' '||' '&'
}
*/

int	execute_command(t_command *command)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->value.simple));//, NO_PIPE, NO_PIPE));
//	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
//		return (execute_connection(command));
	return 1;
}

