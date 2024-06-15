/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:39:45 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:39:46 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

char	**initialize_environ(void)
{
	extern char	**environ;
	char		**my_environ;
	size_t		i;

	if (!environ)
		return (NULL);
	my_environ = xmalloc(sizeof(char *) * (count_strs(environ) + 1));
	i = 0;
	while (environ[i])
	{
		my_environ[i] = ft_strdup(environ[i]);
		i++;
	}
	my_environ[i] = NULL;
	return (my_environ);
}

void	shell_initialize(void)
{
	extern char	**environ;

	signal(SIGQUIT, SIG_IGN);
	environ = initialize_environ();
	init_shell_level();
	init_shell_underscore();
	init_shell_pwd(NO_UPDATE);
	init_shell_oldpwd(NO_UPDATE);
}
