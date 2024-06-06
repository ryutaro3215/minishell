#include "../include/parse.h"

bool	is_blank(char c)
{
	if (c == ' ' || c == '\t')
		return true;
	return false;
}

bool	is_word_component(char c)
{
	if (!isalnum(c) && c != '_' && c != '-' && c != '.' && c != '/' && c != '=' && c != '~' && c != '$' && c != '\'' && c != '\"' && c != '?')
		return false;
	return true;
}

bool	is_word_beggining_component(char c)
{
	if (!isalnum(c) && c != '_' && c != '-' && c != '.' && c != '/' && c!= '=' && c != '~' && c != '$' && c != '\'' && c != '\"' && c != '?')
		return false;
	return true;
}

bool	is_word(char *line)
{
	if (is_word_beggining_component(line[0]))
		return true;
	return false;
}

bool	is_operator(char *line)
{
	if (line[0] == '|')
		return true;
	return false;
}

bool	is_redirect(char *line)
{
	if (strncmp(line, "<<", 2) == 0)
		return true;
	else if (strncmp(line, ">>", 2) == 0)
		return true;
	else if (strncmp(line, ">", 1) == 0)
		return true;
	else if (strncmp(line, "<", 1) == 0)
		return true;
	return false;
}

char	*get_word(char *line)
{
	int	i = 0;
	char	*token;

	while (line[i] && is_word_component(line[i]))
		i++;
	token = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (line[i] && is_word_component(line[i]))
	{
		token[i] = line[i];
		i++;
	}
	token[i] = '\0';
	return token;
}

char	*get_operator(char *line)
{
	char	*token;
	(void)	line;

	token = malloc(sizeof(char) * 2);
	token[0] = '|';
	token[1] = '\0';
	return token;
}

char	*get_redirect(char *line)
{
	char	*token;
	(void)	line;

	if ((strncmp(line, "<<", 2) == 0) || (strncmp(line, ">>", 2) == 0))
	{
		token = malloc(sizeof(char) * 3);
		token[0] = line[0];
		token[1] = line[1];
		token[2] = '\0';
	}
	else //  '<' or '>'
	{
		token = malloc(sizeof(char) * 2);
		token[0] = line[0];
		token[1] = '\0';
	}
	return token;
}

t_token	*add_token(t_token *token_list, char **line, int token_kind)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	new_token->attribute = token_kind;
	if (token_kind == WORD)
		new_token->name = get_word(*line);
	else if (token_kind == OPERATOR)
		new_token->name = get_operator(*line);
	else if (token_kind == REDIRECT)
		new_token->name = get_redirect(*line);
	*line += strlen(new_token->name); // increment line address.
	new_token->next = NULL;
	if (!token_list)
		return new_token;
	else
	{
		tmp = token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
		return token_list;
	}
}

t_token	*tokenize(char *line)
{
	t_token	*token_list = NULL;

	while (*line)
	{
		if (is_blank(*line))
		{
			line++;
			continue;
		}
		else if (is_operator(line))
			token_list = add_token(token_list, &line, OPERATOR);
		else if (is_word(line))
			token_list = add_token(token_list, &line, WORD);
		else if (is_redirect(line))
			token_list = add_token(token_list, &line, REDIRECT);
		else
		{
			if (token_list)
				free_token_list(token_list);
			printf("syntax error: %s\n", line);
			return NULL;
		}
	}
	return token_list;
}
