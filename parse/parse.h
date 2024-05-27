#ifndef PARSE_H
#define PARSE_H

#include "../tokenize/tokenize.h"

enum command_attribute
{
	cm_simple, // 0
	cm_connection // 1
};

enum redirect_attribute
{
	r_input,
	r_output,
	r_heredoc,
	r_append_output
};

enum connector
{
	pipe // 0
	// you can add other operator('||' '&&' '&').
};

typedef struct s_redirect
{
	int					attribute; // referenct "enum redirect_attribute"
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
	int	attribute; // reference "enum command_attribute"
	int	test;
	union
	{
		struct s_simple		*simple;
		struct s_connection	*connection;
	}	value;
}	t_command;

t_command	*parse(t_token *token_list);
t_command	*add_command(t_token *token_list);
void		free_redirect_list(t_redirect *redirect_list);
void		free_command_list(t_command *command_list);

#endif
