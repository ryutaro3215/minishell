#include "../include/exec.h"
#include "../include/env.h"

void	*find_shell_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (&builtin_echo);
	else if (strcmp(command, "cd") == 0)
		return (&builtin_cd);
	else if (strcmp(command, "pwd") == 0)
		return (&builtin_pwd);
	else if (strcmp(command, "export") == 0)
		return (&builtin_export);
	else if (strcmp(command, "unset") == 0)
		return (&builtin_unset);
	else if (strcmp(command, "env") == 0)
		return (&builtin_env);
	else if (strcmp(command, "exit") == 0)
		return (&builtin_exit);
	else
		return NULL;
}

int	builtin_echo(t_token *word_list)
{
	t_token	*current_word;
	int		n_option_flag;

	current_word = word_list->next;
	if (!current_word)
	{
		printf("\n");
		return EXECUTION_SUCCESS;
	}
	n_option_flag = 0;
	if (strcmp(current_word->name, "-n") == 0)
	{
		n_option_flag = 1;
		current_word = current_word->next;
	}
	while (current_word)
	{
		printf("%s", current_word->name);
		current_word = current_word->next;
		if (current_word)
			printf(" ");
	}
	if (!n_option_flag)
		printf("\n");
	return EXECUTION_SUCCESS;
}

int	builtin_cd(t_token *word_list)
{
	if (!word_list->next)
		return EXECUTION_SUCCESS;
	init_shell_oldpwd(UPDATE); // update
	chdir(word_list->next->name);
	init_shell_pwd(UPDATE); // update
	return EXECUTION_SUCCESS;
}

int	builtin_pwd(t_token *word_list)
{
	char	buf[PATH_MAX];

	(void)word_list;
	printf("%s\n", getcwd(buf, PATH_MAX));
	return EXECUTION_SUCCESS;
}

int	builtin_export(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		builtin_env(NULL);
	while (current_token)
	{
		if (strchr(current_token->name, '=')) // when "export =" ... ?
		{
			if (environ_already_exist(current_token->name, EXPORT))
				replace_environ_var(current_token->name);
			else
				add_environ_var(current_token->name);
		}
		current_token = current_token->next;
	}
	return EXECUTION_SUCCESS;
}

int	builtin_unset(t_token *word_list)
{
	t_token	*current_token;

	current_token = word_list->next;
	if (!current_token)
		return EXECUTION_SUCCESS;
	while (current_token)
	{
		if (environ_already_exist(current_token->name, UNSET))
			unset_environ_var(current_token->name);
		current_token = current_token->next;
	}
	return EXECUTION_SUCCESS;
}

int	builtin_env(t_token *word_list)
{
	extern char	**environ;
	char	**tmp;
	(void)word_list;

	tmp = environ;
	if (tmp)
	{
		while (*tmp)
		{
			printf("%s\n", *tmp);
			tmp++;
		}
	}
	return EXECUTION_SUCCESS;
}

int	builtin_exit(t_token *word_list)
{
	(void)word_list;
	printf("exit\n");
	exit(EXECUTION_SUCCESS);
}
