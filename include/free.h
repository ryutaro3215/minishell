/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:21 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:22 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

# include <stdlib.h>

void	free_token_list(t_token *token_list);
void	free_redirect_list(t_redirect *redirect_list);
void	free_simple(t_command *command);
void	free_command_list(t_command *command_list);
void	free_2d_array(char **array);

#endif
