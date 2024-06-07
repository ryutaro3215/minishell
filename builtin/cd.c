#include "../include/builtin.h"

int	builtin_cd(t_token *word_list)
{
	if (!word_list->next)
		return (EXECUTION_SUCCESS);
	init_shell_oldpwd(UPDATE); // update
	chdir(word_list->next->name);
	init_shell_pwd(UPDATE); // update
	return (EXECUTION_SUCCESS);
}
