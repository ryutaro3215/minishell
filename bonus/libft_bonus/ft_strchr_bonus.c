/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kisobe <kisobe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 13:26:09 by kisobe            #+#    #+#             */
/*   Updated: 2024/07/23 19:05:48 by kisobe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		str_len;
	char	*str_finded;
	char	c_conv;

	if (!s)
		return (NULL);
	c_conv = c;
	i = 0;
	str_len = ft_strlen(s);
	while (i <= str_len)
	{
		if (s[i] == c_conv)
		{
			str_finded = (char *)&s[i];
			return (str_finded);
		}
		i++;
	}
	return (NULL);
}
