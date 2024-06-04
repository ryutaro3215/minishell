#include "../include/parse.h"

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (strdup(s2));
	s3 = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

bool	need_here_document(t_token *token_list)
{
	while (token_list)
	{
		if (strcmp(token_list->name, "<<") == 0)
			return true;
		token_list = token_list->next;
	}
	return false;
}

char	*here_document_loop(char *delimiter)
{
	int		EOF_reached;
	char	*line;
	char	*document = NULL;

	EOF_reached = 0;
	while (EOF_reached == 0)
	{
		line = readline("heredoc> ");
		if (!line)
		{
			printf("minishell: warning: reached EOF (need '%s')\n", delimiter);
			EOF_reached = EOF;
			continue;
		}
		if (strcmp(line, delimiter) == 0)
		{
			EOF_reached = EOF;
			free(line);
			continue;
		}
		document = ft_strjoin(document, line);
		document = ft_strjoin(document, "\n");
		free(line);
	}
	return document;
}

void	replace_with_document(t_redirect *current_redirect, char *document)
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
		current_redirect = command_list->value.simple->redirect_list;
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
		gather_here_document(command_list->value.connection->first);
		gather_here_document(command_list->value.connection->second);
	}
}

