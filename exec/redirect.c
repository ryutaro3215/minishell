#include "../include/exec.h"

int	do_r_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return (EXECUTION_FAILURE);
	}
	dup2(fd, 0); // need error check
	close(fd); // need error check
	return (EXECUTION_SUCCESS);
}

int	do_r_output(char *filename)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return (EXECUTION_FAILURE);
	}
	dup2(fd, 1); // need error check
	close(fd); // need error check
	return (EXECUTION_SUCCESS);
}

int	do_r_append_output(char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return (EXECUTION_FAILURE);
	}
	dup2(fd, 1);
	close(fd);
	return (EXECUTION_SUCCESS);
}

int	do_r_here_document(char *filename)
{
	int	fildes[2];

	pipe(fildes); // need error check
	write(fildes[1], filename, strlen(filename));
	dup2(fildes[0], 0);
	close(fildes[0]);
	close(fildes[1]);
	return (EXECUTION_SUCCESS);
}

int	do_redirect(t_redirect *redirect_list)
{
	t_redirect	*current_redirect;
	int			result = EXECUTION_SUCCESS;

	current_redirect = redirect_list;
	if (!current_redirect->filename)
		return EXECUTION_SUCCESS; // redirect doesn't exist.
	while (current_redirect)
	{
		if (current_redirect->attribute == r_input)
			result = do_r_input(current_redirect->filename);
		else if (current_redirect->attribute == r_output)
			result = do_r_output(current_redirect->filename);
		else if (current_redirect->attribute == r_append_output)
			result = do_r_append_output(current_redirect->filename);
		else // (current_redirect->attribute == r_heredoc)
			result = do_r_here_document(current_redirect->filename);
		if (result == EXECUTION_FAILURE)
			return EXECUTION_FAILURE;
		current_redirect = current_redirect->next;
	}
	return EXECUTION_SUCCESS;
}

