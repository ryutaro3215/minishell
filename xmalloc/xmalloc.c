/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:40:56 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:40:57 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/xmalloc.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	handle_error(!ptr && errno == ENOMEM);
	return (ptr);
}
