/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_document.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:40:36 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/07/15 14:38:50 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

extern sig_atomic_t	g_interrupt_state;

bool	need_here_document(t_token *token_list)
{
	while (token_list)
	{
		if (ft_strcmp(token_list->name, "<<") == 0)
			return (true);
		token_list = token_list->next;
	}
	return (false);
}

static bool	is_end_of_heredoc(char **line, char **document, char *delimiter)
{
	if (!(*line))
	{
		ft_err_printf("minishell: reached EOF (need '%s')\n", delimiter);
		if (!(*document))
			*document = ft_strdup("");
		return (true);
	}
	else if (**line == '\0' && g_interrupt_state)
	{
		free(*line);
		free(*document);
		*document = NULL;
		return (true);
	}
	else if (ft_strcmp(*line, delimiter) == 0)
	{
		free(*line);
		return (true);
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
		signal(SIGINT, sigint_handler_for_readline);
		rl_event_hook = event_hook_for_readline;
		line = readline("heredoc> ");
		rl_event_hook = 0;
		if (is_end_of_heredoc(&line, &document, delimiter))
		{
			eof_reached = 1;
			continue ;
		}
		document = ft_strjoin(document, line);
		document = strjoin_but_freed_only_first_arg(document, "\n");
	}
	signal(SIGINT, sigint_handler_for_exec);
	return (document);
}

static void	replace_with_document(t_redirect *current_redirect, char *document)
{
	free(current_redirect->filename);
	current_redirect->filename = document;
}

int	gather_here_document(t_command *command_list)
{
	char		*document;
	t_redirect	*current_redirect;

	if (command_list->attribute == cm_simple)
	{
		current_redirect = command_list->u_value.simple->redirect_list;
		while (current_redirect)
		{
			if (current_redirect->attribute == r_heredoc)
			{
				document = here_document_loop(current_redirect->filename);
				if (!document && g_interrupt_state)
					return (HEREDOC_FAILURE);
				replace_with_document(current_redirect, document);
			}
			current_redirect = current_redirect->next;
		}
	}
	else
	{
		gather_here_document(command_list->u_value.connection->first);
		gather_here_document(command_list->u_value.connection->second);
	}
	return (HEREDOC_SUCCESS);
}
