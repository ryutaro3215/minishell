/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirect_wildcard_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryutaro320515 <ryutaro320515@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:52:40 by ryutaro3205       #+#    #+#             */
/*   Updated: 2024/06/15 13:52:41 by ryutaro3205      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/expand_bonus.h"

static char	*store_given_word_to_add_new_words(t_redirect *current_redirect)
{
	char	*given_filename;

	given_filename = ft_strdup(current_redirect->filename);
	free(current_redirect->filename);
	current_redirect->filename = NULL;
	return (given_filename);
}

static int	read_directory(DIR *dirp, char *given_filename,
	t_redirect *current_redirect)
{
	int				already_matched;
	struct dirent	*dp;

	already_matched = 0;
	while (1)
	{
		dp = readdir(dirp);
		if (!dp)
			return (0);
		if (ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0)
			continue ;
		if (pattern_match(given_filename, dp->d_name))
		{
			if (already_matched == 1)
				return (-1);
			already_matched = 1;
			current_redirect->filename = ft_strdup(dp->d_name);
		}
	}
}

int	expand_redirect_wildcard(t_redirect *current_redirect)
{
	char			*given_filename;
	DIR				*dirp;

	if (!ft_strchr(current_redirect->filename, '*'))
		return (EXECUTION_SUCCESS);
	dirp = opendir(".");
	if (!dirp)
	{
		write(2, "minishell: open failed\n", 24);
		return (EXECUTION_FAILURE);
	}
	given_filename = store_given_word_to_add_new_words(current_redirect);
	if (read_directory(dirp, given_filename, current_redirect) < 0)
	{
		closedir(dirp);
		free(given_filename);
		write(2, "minishell: Ambiguous redirect\n", 31);
		return (EXECUTION_FAILURE);
	}
	closedir(dirp);
	if (!current_redirect->filename)
		current_redirect->filename = given_filename;
	else
		free(given_filename);
	return (EXECUTION_SUCCESS);
}
