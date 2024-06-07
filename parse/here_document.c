#include "../include/parse.h"

bool	need_here_document(t_token *token_list)
{
	while (token_list)
	{
		if (strcmp(token_list->name, "<<") == 0)
			return (true);
		token_list = token_list->next;
	}
	return (false);
}

static char	*here_document_loop(char *delimiter)
{
	int		eof_reached;
	char	*line;
	char	*document;

	eof_reached = 0;
	document = NULL;
	while (eof_reached == 0)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			printf("minishell: warning: reached EOF (need '%s')\n", delimiter);
			eof_reached = EOF;
			continue ;
		}
		if (strcmp(line, delimiter) == 0)
		{
			eof_reached = EOF;
			free(line);
			continue ;
		}
		document = ft_strjoin(document, line);
		document = strjoin_but_freed_only_first_arg(document, "\n");
	}
	return (document);
}

static void	replace_with_document(t_redirect *current_redirect, char *document)
{
	free(current_redirect->filename);
	current_redirect->filename = document;
}

void	gather_here_document(t_command *command_list)
{
	char		*document;
	t_redirect	*current_redirect;

	if (command_list->attribute == cm_simple)
	{
		current_redirect = command_list->u_value.simple->redirect_list;
		if (!current_redirect->filename)
			return ;
		while (current_redirect)
		{
			if (current_redirect->attribute == r_heredoc)
			{
				document = here_document_loop(current_redirect->filename); // delimiter
				replace_with_document(current_redirect, document);
			}
			current_redirect = current_redirect->next;
		}
	}
	else // command_list->attribute == cm_connection
	{
		gather_here_document(command_list->u_value.connection->first);
		gather_here_document(command_list->u_value.connection->second);
	}
}
