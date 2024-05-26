#include "tokenize/tokenize.h"
#include "parse/parse.h"

int	main()
{
	char	*line = "ls | wc -l | ls | pwd -a -b -d | abcdefghijk hello world";
	t_token	*token_list;

	token_list = tokenize(line);
	printf("token_list:\n");
	t_token	*tmp = token_list;
	while (tmp)
	{
		printf("%s -> ", tmp->name);
		tmp = tmp->next;
	}
	printf("(null)\n\n");

	t_command	*command_list;
	command_list = parse(token_list);
	if (!command_list)
	{
		printf("parse return NULL\n");
		return 0;
	}
	free_token_list(token_list);
	free_command_list(command_list);
	return 0;
}

__attribute__((destructor))
static void	destructor()
{
	system("leaks -q a.out");
}
