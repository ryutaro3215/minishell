/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:43 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:44 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/libft_bonus.h"

static int	ft_if_minus(int *i_p, const char *str)
{
	int	if_minus;

	if_minus = 1;
	if ((str[*i_p] == '-') || (str[*i_p] == '+'))
	{
		if (('0' <= str[*i_p + 1]) && (str[*i_p + 1] <= '9'))
		{
			if (str[*i_p] == '-')
				if_minus = -1;
			(*i_p)++;
		}
	}
	return (if_minus);
}

static int	change_to_int(int i, const char *str, int result)
{
	int	int_num;

	while (('0' <= str[i]) && (str[i] <= '9'))
	{
		int_num = str[i] - 48;
		result = result * 10;
		result = result + int_num;
		i++;
	}
	return (result);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	if_minus;
	int	result;

	i = 0;
	while (str[i])
	{
		result = 0;
		if_minus = ft_if_minus(&i, str);
		if (('0' <= str[i]) && (str[i] <= '9'))
		{
			result = change_to_int(i, str, result);
			return (result * if_minus);
		}
		else if ((9 <= str[i]) && (str[i] <= 13))
			i++;
		else if (32 == str[i])
			i++;
		else
			return (0);
	}
	return (0);
}
