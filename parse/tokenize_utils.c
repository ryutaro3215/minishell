/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmatsuba <rmatsuba@student.42tokyo.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:43:54 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/12 10:21:18 by rmatsuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

bool	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

bool	check_conope(char c)
{
	if (c == '|' || c == '&')
		return (true);
	else
		return (false);
}

bool	check_redope(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

void	skip_space(char **str)
{
	while (check_space(**str))
		(*str)++;
}

int	check_quote(char str)
{
	if (str == '\"')
		return (2);
	else if (str == '\'')
		return (1);
	else
		return (0);
}
