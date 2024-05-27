/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:59:23 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/05/27 20:52:40 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token t_token;

enum token_type
{
	WORD = 1,
	CON_OPE,
	RED_OPE
};

typedef struct s_token
{
	char			*word;
	int				type;
	struct s_token	*next;
}	t_token;



#endif
