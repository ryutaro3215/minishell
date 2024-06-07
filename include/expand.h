#ifndef EXPAND_H
#define EXPAND_H

#include "../include/parse.h"

// expand.c
void	expand_words(t_simple *simple, int last_command_exit_status);

// expand_dollar.c
void	expand_dollar(t_token *current_word, int last_command_exit_status);

// expand_quote.c
void	remove_quote(t_token *current_word);

// expand_wildcard.c
void	expand_wildcard(t_token *current_word);

// expand_dollar_utils.c
char	*skip_single_quote(char *new_word, char **old_word);
char	*handle_dollar_only(char *new_word, char **old_word);
char	*handle_question(char *new_word, char **old_word, int last_command_exit_status);
char	*handle_environment_variable(char *new_word, char **old_word, char *env_name);
char	*skip_char(char *new_word, char ** old_word);

// expand_utils.c
bool	pattern_match(char *given_word, char *filename);
void	add_new_word(t_token *current_word, char *filename);
t_token	*delete_current_word(t_simple *simple, t_token *current_word);
char	*get_env_value(char *env_name);
char	*get_env_name(char *word);
char	*get_last_double_quote(char *word);
char	*get_last_single_quote(char *word);
char	*append_char(char *word, char c);

#endif
