/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quote_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:38:34 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:38:35 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/expand.h"

char	*get_last_double_quote(char *word)
{
	word++; // skip first double quote.
	return (ft_strchr(word, '\"'));
}

char	*get_last_single_quote(char *word)
{
	word++; // skip first single quote.
	return (ft_strchr(word, '\''));
}
