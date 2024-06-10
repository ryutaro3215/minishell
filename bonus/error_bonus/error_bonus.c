#include "../include_bonus/error_bonus.h"

void	handle_error(bool is_error)
{
	if (is_error && errno != 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (is_error && errno == 0)
	{
		ft_err_printf("minishell: Unknown error\n");
		exit(EXIT_FAILURE);
	}
}
