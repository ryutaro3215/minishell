/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:53:05 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:53:06 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_BONUS_H
# define EVAL_BONUS_H

# include "parse_bonus.h"
# include "exec_bonus.h"

# include <readline/history.h>

# define PARSE_ERROR 2

int	eval(char *line, int last_command_exit_status);

#endif
