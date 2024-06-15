/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:55:07 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 14:17:37 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/xmalloc_bonus.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	handle_error(!ptr && errno == ENOMEM);
	return (ptr);
}
