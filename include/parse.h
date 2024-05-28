#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


// tokenize.c
enum token_attribute
{
	WORD,
	OPERATOR,
	REDIRECT
};

typedef struct s_token
{
	int				attribute; // reference "enum token_attribute"
	char			*name;
	struct s_token	*next;
}	t_token;


bool	is_blank(char c);
bool	is_word_component(char c);
bool	is_word_beggining_component(char c);
bool	is_word(char *line);
bool	is_operator(char *line);
bool	is_redirect(char *line);
char	*get_word(char *line);
char	*get_operator(char *line);
char	*get_redirect(char *line);


// parse.h
t_token	*add_token(t_token *token_list, char **line, int token_kind);
t_token	*tokenize(char *line);

enum command_attribute
{
	cm_simple, // 0
	cm_connection // 1
};

enum redirect_attribute
{
	r_input, // 0
	r_output, // 1
	r_heredoc, // 2
	r_append_output // 3
};

enum connector
{
	pipeline // 0
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
	int					connector; // reference "enum connector"
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

#include "free.h"

// create new struct
t_command		*create_new_command();
t_simple		*create_new_simple();
t_connection	*create_new_connection();
t_token			*copy_token(t_token *word_list, t_token *current_token);
t_redirect		*copy_redirect(t_redirect *redirect_list, t_token *current_token);
t_token			*create_word_list(t_token *token_list);
t_redirect		*create_redirect_list(t_token *token_list);

t_command		*add_simple_command(t_token *token_list);
t_command		*add_connection(t_token *token_list);
t_command		*add_command(t_token *token_list);

// get
int				detect_cm_attribute(t_token *token_list);
int				get_redirect_attribute(char *redirect_name);
int				get_connector(t_token *token_list);
t_token			*get_first_token_list(t_token *token_list);
t_token			*get_second_token_list(t_token *token_list);

// parse
t_command		*parse(t_token *token_list);


#endif
