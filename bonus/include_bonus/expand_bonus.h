/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:11 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 14:15:42 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_BONUS_H
# define EXPAND_BONUS_H

# include "exec_bonus.h"
# include "minishell_bonus.h"
# include "environ_bonus.h"
# include "libft_bonus.h"

# include <stdbool.h>
# include <dirent.h>

// expand.c
int		expand(t_simple *simple, int last_command_exit_status);
void	expand_words(t_simple *simple, int last_command_exit_status);
int		expand_redirects(t_simple *simple, int last_command_exit_status);

// expand_dollar.c
void	expand_dollar(t_token *current_word, int last_command_exit_status);
void	expand_redirect_dollar(t_redirect *current_redirect,
			int last_command_exit_status);
char	*get_env_value(char *env_name);
char	*get_env_name(char *word);

// expand_quote.c
void	remove_quote(t_token *current_word);
void	remove_redirect_quote(t_redirect *current_redirect);

// expand_wildcard.c
void	expand_wildcard(t_token *current_word);

// expand_redirect_wildcard.c
int		expand_redirect_wildcard(t_redirect *current_redirect);

// expand_dollar_utils.c
char	*skip_single_quote(char *new_word, char **old_word);
char	*handle_dollar_only(char *new_word, char **old_word);
char	*handle_question(char *new_word, char **old_word,
			int last_command_exit_status);
char	*handle_environment_variable(char *new_word,
			char **old_word, char *env_name);
char	*skip_char(char *new_word, char **old_word);

// expand_quote_utils.c
char	*get_last_single_quote(char *word);
char	*get_last_double_quote(char *word);

// expand_wildcard_utils.c
bool	pattern_match(char *given_word, char *filename);

// expand_utils.c
void	add_new_word(t_token *current_word, char *filename);
t_token	*delete_current_word(t_simple *simple, t_token *current_word);
char	*append_char(char *word, char c);

#endif
