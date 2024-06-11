#include "../include_bonus/expand_bonus.h"

static void	retrieve_next_word(t_token *current_word, char *given_word,
	t_token *next_word)
{
	if (!current_word->name)
		current_word->name = given_word;
	else
	{
		while (current_word->next)
			current_word = current_word->next;
		current_word->next = next_word;
		free(given_word);
	}
}

static char	*store_given_word_to_add_new_words(t_token *current_word)
{
	char	*given_word;

	given_word = ft_strdup(current_word->name);
	free(current_word->name);
	current_word->name = NULL;
	return (given_word);
}

static void	read_directory_loop(DIR *dirp, char *given_word,
	t_token *current_word)
{
	struct dirent	*dp;

	while (1)
	{
		dp = readdir(dirp);
		if (!dp)
			break ;
		if (ft_strcmp(dp->d_name, ".") == 0 || ft_strcmp(dp->d_name, "..") == 0)
			continue ;
		if (ft_strcmp(given_word, "*") == 0 && ft_strncmp(dp->d_name, ".", 1) == 0)
			continue;
		if (pattern_match(given_word, dp->d_name))
			add_new_word(current_word, dp->d_name);
	}
}

void	expand_wildcard(t_token *current_word)
{
	char			*given_word;
	DIR				*dirp;
	t_token			*next_word;

	if (!ft_strchr(current_word->name, '*'))
		return ;
	dirp = opendir(".");
	if (!dirp)
	{
		ft_err_printf("minishell: open failed\n");
		return ;
	}
	given_word = store_given_word_to_add_new_words(current_word);
	next_word = current_word->next;
	read_directory_loop(dirp, given_word, current_word);
	closedir(dirp);
	retrieve_next_word(current_word, given_word, next_word);
}
