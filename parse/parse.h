#ifndef PARSE_H
#define PARSE_H

#include "../tokenize/tokenize.h"

enum command_attribute
{
	cm_simple, // 0
	cm_connection // 1
};

enum connector
{
	pipe
	// you can add other operator('||' '&&' '&').
};

typedef struct s_simple
{
	struct s_token		*word_list;
	struct s_redirect	*redirect_list;
}	t_simple;

typedef struct s_connection
{
	struct s_command	*first;
	struct s_command	*second;
	int					connector;
}	t_connection;

typedef struct s_command
{
	int	attribute; // reference "enum command_attribute"
	union
	{
		struct s_simple		*simple;
		struct s_connection	*connection;
	}	value;
}	t_command;

t_command	*parse(t_token *token_list);
t_command	*add_command(t_token *token_list);
void		free_command_list(t_command *command_list);

#endif
