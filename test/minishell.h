/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:59:23 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/07 23:56:07 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

enum token_attr
{
	WORD = 1,
	CON_OPE,
	RED_OPE
};

typedef struct s_token
{
	char			*word;
	int				attr;
	struct s_token	*next;
}	t_token;

enum	command_attr
{
	SIMPLE_COMMAND,
	CONNECTOR,
};

typedef struct	s_simple
{
	struct s_token	*token;
}				t_simple;

typedef struct	s_connector
{
	int		connector_attr;
	struct s_command	*left;
	struct s_command	*right;
}				t_connector;

typedef struct	s_command
{
	int		com_attr;
	union
	{
		struct s_simple	*simple_command;
		struct s_connector	*connector;
	} command;
}				t_command;

#endif
