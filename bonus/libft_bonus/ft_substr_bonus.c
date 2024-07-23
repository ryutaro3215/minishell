/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:40:19 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/07/20 19:31:54 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

static char	*ft_input_str(size_t len, unsigned int start, char const *s)
{
	size_t	s_len;
	size_t	i;
	char	*s_copy;

	s_len = ft_strlen(s);
	if (s_len < len)
		len = s_len;
	if (s_len < start)
		len = 0;
	s_copy = xmalloc((len + 1) * sizeof(char));
	if (s_copy == NULL)
		return (NULL);
	i = 0;
	while ((i < len) && (s[i]))
	{
		s_copy[i] = s[i + start];
		i++;
	}
	s_copy[i] = '\0';
	return (s_copy);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*s_copy;

	if (s == NULL)
		return (NULL);
	if (len == 0)
	{
		s_copy = xmalloc(1);
		if (s_copy == NULL)
			return (NULL);
		s_copy[0] = '\0';
		return (s_copy);
	}
	if ((SIZE_MAX - 1) / len < sizeof(char))
		return (NULL);
	s_copy = ft_input_str(len, start, s);
	return (s_copy);
}
