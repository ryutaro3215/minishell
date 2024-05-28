#include "../include/exec.h"

void	do_r_input(char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return ;
	}
	dup2(fd, 0); // need error check
	close(fd); // need error check
}

void	do_r_output(char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return ;
	}
	dup2(fd, 1); // need error check
	close(fd); // need error check
}

void	do_r_append_output(char *filename)
{
	int		fd;

	fd = open(filename, O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
	{
		printf("internal error: open\n");
		return ;
	}
	dup2(fd, 1);
	close(fd);
}

void	do_redirect(t_redirect *redirect_list)
{
	t_redirect	*current_redirect;

	current_redirect = redirect_list;
	if (!current_redirect->filename)
		return ; // redirect doesn't exist.
	while (current_redirect)
	{
		if (current_redirect->attribute == r_input)
			do_r_input(current_redirect->filename);
		else if (current_redirect->attribute == r_output)
			do_r_output(current_redirect->filename);
		else if (current_redirect->attribute == r_append_output)
			do_r_append_output(current_redirect->filename);
		current_redirect = current_redirect->next;
	}
}

