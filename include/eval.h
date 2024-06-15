/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:12 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:13 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVAL_H
# define EVAL_H

# include "parse.h"
# include "exec.h"

# include <readline/history.h>

# define PARSE_ERROR 2

int	eval(char *line, int last_command_exit_status);

#endif
