#include "../include/exec.h"

void	expand_dollar(t_token *current_word, int last_command_exit_status)
{
	char	*new_word;
	char	*old_word;
	char	*last_single_quote;
	char	*inside_single_quote;
	char	*env_name;
	char	*env_value;
	char	*exit_status;

	new_word = NULL;
	old_word = current_word->name;
	while (*old_word)
	{
		if (*old_word == '\'')
		{
			last_single_quote = get_last_single_quote(old_word);
			inside_single_quote = ft_substr(old_word, 0, last_single_quote - old_word + 1);
			old_word += strlen(inside_single_quote);
			new_word = ft_strjoin(new_word, inside_single_quote);
		}
		else if (*old_word == '$')
		{
			env_name = get_env_name(old_word);
			if (!env_name) // when dollar only "$"
			{
				new_word = append_char(new_word, *old_word);
				old_word++;
			}
			else if (strcmp(env_name, "?") == 0)
			{
				exit_status = ft_itoa(last_command_exit_status);
				new_word = ft_strjoin(new_word, exit_status);
				old_word += 2; // $?
			}
			else
			{
				env_value = get_env_value(env_name);
				if (!env_value)
					old_word += strlen(env_name) + 1; // 1 is num of "$".
				else
				{
					old_word += strlen(env_name) + 1;
					new_word = ft_strjoin(new_word, env_value);
				}
			}
			free(env_name);
		}
		else
		{
			new_word = append_char(new_word, *old_word);
			old_word++;
		}
	}
	free(current_word->name);
	current_word->name = new_word;
}

void	remove_quote(t_token *current_word)
{
	char	*old_word;
	char	*new_word;
	char	*last_single_quote;
	char	*last_double_quote;
	char	*inside_single_quote;
	char	*inside_double_quote;

	old_word = current_word->name;
	if (!strchr(old_word, '\'') && !strchr(old_word, '\"'))
		return ;
	new_word = NULL;
	while (*old_word)
	{
		if (*old_word == '\'')
		{
			last_single_quote = get_last_single_quote(old_word);
			old_word++;
			inside_single_quote = ft_substr(old_word, 0, last_single_quote - old_word);
			old_word += strlen(inside_single_quote) + 1;
			new_word = ft_strjoin(new_word, inside_single_quote);
		}
		else if (*old_word == '\"')
		{
			last_double_quote = get_last_double_quote(old_word);
			old_word++;
			inside_double_quote = ft_substr(old_word, 0, last_double_quote - old_word);
			old_word += strlen(inside_double_quote) + 1;
			new_word = ft_strjoin(new_word, inside_double_quote);
		}
		else
		{
			new_word = append_char(new_word, *old_word);
			old_word++;
		}
	}
	free(current_word->name);
	current_word->name = new_word;
}

void	expand_wildcard(t_token *current_word)
{
	char	*given_word;
	DIR		*dirp;
	int		end_of_dirent;
	struct dirent	*dp;
	t_token	*next_word;

	if (!strchr(current_word->name, '*'))
		return ;
	dirp = opendir(".");
	if (!dirp)
	{
		printf("minishell: open failed\n");
		return ;
	}
	given_word = strdup(current_word->name);
	free(current_word->name);
	current_word->name = NULL;
	next_word = current_word->next;
	end_of_dirent = 0;
	while (end_of_dirent == 0)
	{
		dp = readdir(dirp);
		if (!dp)
		{
			end_of_dirent = 1;
			continue;
		}
		if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;
		if (pattern_match(given_word, dp->d_name))
			add_new_word(current_word, dp->d_name);
	}
	closedir(dirp);
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

void	expand_words(t_simple *simple, int last_command_exit_status)
{
	t_token	*current_word;
	char	*dollar;

	current_word = simple->word_list;
	while (current_word)
	{
		dollar = strchr(current_word->name, '$');
		if (dollar)
		{
			expand_dollar(current_word, last_command_exit_status);
			if (!current_word->name)
				current_word = delete_current_word(simple, current_word);
			else
			{
				expand_wildcard(current_word);
				remove_quote(current_word);
				current_word = current_word->next;
			}
		}
		else
		{
			expand_wildcard(current_word);
			remove_quote(current_word);
			current_word = current_word->next;
		}
	}
}
