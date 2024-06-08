#ifndef MINISHELL_H
# define MINISHELL_H


# include <readline/readline.h>
# include <readline/history.h>

// tokenize
enum e_token_attribute
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

// parse
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
	pipeline
};

typedef struct s_redirect
{
	int					attribute; // reference "enum redirect_attribute"
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
	int	test; // unused ?
	union
	{
		struct s_simple		*simple;
		struct s_connection	*connection;
	}	u_value;
}	t_command;

int			reader_loop(int *EOF_reached, int last_command_exit_status);

#endif
