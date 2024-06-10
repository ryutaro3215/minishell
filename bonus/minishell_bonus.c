#include "include_bonus/minishell_bonus.h"
#include "include_bonus/libft_bonus.h"
#include "include_bonus/init_bonus.h"
#include "include_bonus/signal_bonus.h"
#include "include_bonus/environ_bonus.h"
#include "include_bonus/eval_bonus.h"
#include "include_bonus/free_bonus.h"

int	reader_loop(int *EOF_reached, int last_command_exit_status)
{
	extern char	**environ;
	char		**tmp;
	char		*line;

	signal(SIGINT, sigint_handler_for_readline);
	tmp = environ;
	line = readline("minishell $ ");
	environ = tmp;
	if (!line)
	{
		*EOF_reached = EOF;
		free_2d_array(tmp);
		return (last_command_exit_status);
	}
	signal(SIGINT, sigint_handler_for_exec);
	last_command_exit_status = sigint_is_traped(last_command_exit_status);
	if (*line)
		last_command_exit_status = eval(line, last_command_exit_status);
	free(line);
	return (last_command_exit_status);
}

int	main(void)
{
	int	eof_reached;
	int	last_command_exit_status;

	eof_reached = 0;
	last_command_exit_status = 0;
	shell_initialize();
	while (eof_reached == 0)
		last_command_exit_status
			= reader_loop(&eof_reached, last_command_exit_status);
	ft_err_printf("exit\n");
	return (last_command_exit_status);
}
