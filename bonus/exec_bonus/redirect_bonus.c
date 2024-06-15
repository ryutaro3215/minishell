#include "../include_bonus/exec_bonus.h"

int	do_r_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_err_printf("minishell: %s: No such file or directory\n", filename);
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, 0) == -1)
	{
		ft_err_printf("dup error\n");
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	do_r_output(char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_err_printf("minishell: %s: No such file or directory\n", filename);
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_err_printf("dup error\n");
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	do_r_append_output(char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		ft_err_printf("minishell: %s: No such file or directory\n", filename);
		return (EXECUTION_FAILURE);
	}
	if (dup2(fd, 1) == -1)
	{
		ft_err_printf("dup error\n");
		return (EXECUTION_FAILURE);
	}
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	do_r_here_document(char *filename)
{
	int	fildes[2];

	if (pipe(fildes) == -1)
	{
		ft_err_printf("pipe error\n");
		return (EXECUTION_FAILURE);
	}
	write(fildes[1], filename, ft_strlen(filename));
	if (dup2(fildes[0], 0) == -1)
	{
		ft_err_printf("dup error\n");
		return (EXECUTION_FAILURE);
	}
	close(fildes[0]);
	close(fildes[1]);
	return (EXECUTION_SUCCESS);
}

int	do_redirect(t_redirect *redirect_list)
{
	t_redirect	*current_redirect;
	int			result;

	result = EXECUTION_SUCCESS;
	current_redirect = redirect_list;
	if (!current_redirect->filename)
		return (EXECUTION_SUCCESS);
	while (current_redirect)
	{
		if (current_redirect->attribute == r_input)
			result = do_r_input(current_redirect->filename);
		else if (current_redirect->attribute == r_output)
			result = do_r_output(current_redirect->filename);
		else if (current_redirect->attribute == r_append_output)
			result = do_r_append_output(current_redirect->filename);
		else
			result = do_r_here_document(current_redirect->filename);
		if (result == EXECUTION_FAILURE)
			return (EXECUTION_FAILURE);
		current_redirect = current_redirect->next;
	}
	return (EXECUTION_SUCCESS);
}
