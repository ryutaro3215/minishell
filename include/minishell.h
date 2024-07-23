/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:30 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/07/20 19:00:00 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

enum e_token_attribute
{
	WORD,
	OPERATOR,
	REDIRECT
};

typedef struct s_token
{
	int				attribute;
	char			*name;
	struct s_token	*next;
}	t_token;

enum e_command_attribute
{
	cm_simple,
	cm_connection
};

enum e_redirect_attribute
{
	r_input,
	r_output,
	r_heredoc,
	r_append_output
};

enum e_connector
{
	pipeline,
	andlist,
	orlist
};

typedef struct s_redirect
{
	int					attribute;
	char				*filename;
	struct s_redirect	*next;
}	t_redirect;

typedef struct s_simple
{
	struct s_token		*word_list;
	struct s_redirect	*redirect_list;
}	t_simple;

typedef struct s_connection
{
	int					connector;
	struct s_command	*first;
	struct s_command	*second;
}	t_connection;

typedef struct s_command
{
	int	attribute;
	int	test;
	union
	{
		struct s_simple		*simple;
		struct s_connection	*connection;
	}	u_value;
}	t_command;

int			reader_loop(int *EOF_reached, int last_command_exit_status);

#endif
