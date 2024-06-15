/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:24 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 14:22:10 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_BONUS_H
# define PARSE_BONUS_H

# include "exec_bonus.h"
# include "free_bonus.h"
# include "libft_bonus.h"
# include "signal_bonus.h"
# include "xmalloc_bonus.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <ctype.h>
# include <errno.h>
# include <readline/readline.h>

# define HEREDOC_SUCCESS 1
# define HEREDOC_FAILURE 2

// tokenize.c
t_token			*new_word_token(char **str);
t_token			*new_ope_token(char **str);
bool			check_space(char c);
bool			check_redope(char c);
bool			check_conope(char c);
int				check_quote(char str);
void			skip_space(char **str);
int				get_word_len(char *str);
t_token			*tokenize(char *line);

// create_new_struct.c
t_command		*create_new_command(void);
t_simple		*create_new_simple(void);
t_connection	*create_new_connection(void);
t_token			*create_word_list(t_token *token_list);
t_redirect		*create_redirect_list(t_token *token_list);

// copy_struct.c
t_token			*copy_token(t_token *word_list, t_token *current_token);
t_redirect		*copy_redirect(t_redirect *redirect_list,
					t_token *current_token);

// get_info.c
int				get_cm_attribute(t_token *token_list);
int				get_redirect_attribute(char *redirect_name);
int				get_connector(t_token *token_list);
t_token			*get_first_token_list(t_token *token_list);
t_token			*get_second_token_list(t_token *token_list);

// parse_utils.c
t_command		*add_simple_type_command(void);
t_command		*add_connection_elem(t_command *new_command,
					t_token *first_token_list, t_token *second_token_list);
t_command		*add_connection_type_command(void);

// parse.c
t_command		*parse(t_token *token_list);
t_command		*add_simple_command(t_token *token_list);
t_command		*add_connection(t_token *token_list);
t_command		*add_command(t_token *token_list);

// here_document.c
bool			need_here_document(t_token *token_list);
int				gather_here_document(t_command *command_list);

// parse_cmd.c
t_command		*parse_command(char *line);

#endif
