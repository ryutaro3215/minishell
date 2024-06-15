/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:43:54 by rmatsuba          #+#    #+#             */
/*   Updated: 2024/06/15 14:09:27 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/parse_bonus.h"

static bool	check_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	else
		return (false);
}

static bool	check_conope(char c)
{
	if (c == '|' || c == '&')
		return (true);
	else
		return (false);
}

static bool	check_redope(char c)
{
	if (c == '<' || c == '>')
		return (true);
	else
		return (false);
}

static void	skip_space(char **str)
{
	while (check_space(**str))
		(*str)++;
}

static int	check_quote(char str)
{
	if (str == '\"')
		return (2);
	else if (str == '\'')
		return (1);
	else
		return (0);
}
