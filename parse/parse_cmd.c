#include "../include/parse.h"

t_command	*parse_command(char *line)
{
	t_token		*token_list;
	t_command	*command_list;

	token_list = tokenize(line);
	command_list = parse(token_list);
	if (!command_list)
		return (NULL);
	if (need_here_document(token_list))
	{
		if (gather_here_document(command_list) == HEREDOC_FAILURE)
		{
			free_token_list(token_list);
			free_command_list(command_list);
			return (NULL);
		}
	}
	free_token_list(token_list);
	return (command_list);
}
