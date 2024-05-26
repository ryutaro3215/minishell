#ifndef TOKENIZE_H
#define TOKENIZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

enum
{
	WORD,
	OPERATOR
};

typedef struct s_token
{
	int				attribute;
	char			*name;
	struct s_token	*next;
}	t_token;

t_token	*tokenize(char *line);
void	free_token_list(t_token *token_list);

#endif
