#include "../include_bonus/builtin_bonus.h"

int	builtin_env(t_token *word_list)
{
	extern char	**environ;
	char		**tmp;

	(void)word_list;
	tmp = environ;
	if (tmp)
	{
		while (*tmp)
		{
			ft_printf("%s\n", *tmp);
			tmp++;
		}
	}
	return (EXECUTION_SUCCESS);
}
