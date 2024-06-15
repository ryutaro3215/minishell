/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:37 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:58:54 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/expand_bonus.h"

char	*get_last_double_quote(char *word)
{
	word++;
	return (ft_strchr(word, '\"'));
}

char	*get_last_single_quote(char *word)
{
	word++;
	return (ft_strchr(word, '\''));
}
