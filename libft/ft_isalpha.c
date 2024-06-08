#include "../include/libft.h"

bool	ft_isalpha(int c)
{
	if ((('A' <= c) && (c <= 'Z')) || (('a' <= c) && (c <= 'z')))
		return (true);
	return (false);
}
