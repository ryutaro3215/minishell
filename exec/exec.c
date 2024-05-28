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

int	execute_in_subshell(t_simple *simple, int pipe_in, int pipe_out) //, func *builtin)
{
	pid_t	pid;
	char	*path;
	char	**argv;

	pid = fork();
	if (pid < 0)
		return (EXECUTION_FAILURE);
	if (pid == 0)
	{
		if (pipe_in != NO_PIPE)
		{
			dup2(pipe_in, 0); // need error check
			close(pipe_in); // need error check
		}
		if (pipe_out != NO_PIPE)
		{
			dup2(pipe_out, 1);
			close(pipe_out);
		}
		path = get_path(simple->word_list->name);
		argv = get_argv(simple->word_list);
		do_redirect(simple->redirect_list);
//		if (builtin)
//			exit(execute_builtin());
		exit(execute_disk_command(path, argv));
	}
	if (pipe_in != NO_PIPE)
		close(pipe_in);
	if (pipe_out != NO_PIPE)
		close(pipe_out);
	return (wait(NULL));
//	}
}

int	execute_simple_command(t_simple *simple, int pipe_in, int pipe_out)
{
//	func	*builtin = find_shell_builtin(simple); // return function pointer
//	if (builtin && (pipe_in == NO_PIPE && pipe_out == NO_PIPE))
//		return (execute_builtin(simple, builtin));
	return (execute_in_subshell(simple, pipe_in, pipe_out)); //, builtin));
}

int	execute_pipeline(t_command *command, int pipe_in, int pipe_out)
{
	int	fildes[2];

	if (pipe(fildes) < 0)
	{
		printf("internal error: pipe\n");
		return (EXECUTION_FAILURE);
	}
	execute_command_internal(command->value.connection->first, pipe_in, fildes[1]);
	return (execute_command_internal(command->value.connection->second, fildes[0], pipe_out));
}

int	execute_connection(t_command *command, int pipe_in, int pipe_out)
{
//	int	connector = command->value.connection->connector;

	// if (connector == pipe)
	return (execute_pipeline(command, pipe_in, pipe_out));
	// else if (connector == ...) you can add '&&' '||' '&'
}

int	execute_command_internal(t_command *command, int pipe_in, int pipe_out)
{
	if (command->attribute == cm_simple) // just word list
		return (execute_simple_command(command->value.simple, pipe_in, pipe_out));
	else // (command->attribute == cm_connection) // pipe (and '&&', '||', ';')
		return (execute_connection(command, pipe_in, pipe_out));
}

int	execute_command(t_command *command)
{
	return (execute_command_internal(command, NO_PIPE, NO_PIPE));
}

