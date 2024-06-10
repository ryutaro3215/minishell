#include "../include_bonus/libft_bonus.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	size_t	i;

	p = (char *)xmalloc((n + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
