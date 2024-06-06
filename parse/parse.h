/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:59:23 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/06 13:20:52 by rmatsuba         ###   ########.fr       */
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

enum	commond_attr
{
	SIMPLE_COMMOND,
	CONNECTOR,
}

typedef struct	s_simple
{
	t_token	*word;
}				t_simple;

typedef struct	s_connector
{
	int		connector_attr;
	t_commond	*left;
	t_commond	*right;
}				t_connector;

typedef struct	s_commond
{
	int		com_attr;
	union
	{
		t_simple	*simple_commond;
		t_connector	*connector;
	} commond;
}				t_commond;


#endif
