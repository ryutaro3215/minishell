#include "../include_bonus/builtin_bonus.h"

int	builtin_pwd(t_token *word_list)
{
	char	buf[PATH_MAX];

	(void)word_list;
	ft_printf("%s\n", getcwd(buf, PATH_MAX));
	return (EXECUTION_SUCCESS);
}
