#include "../include_bonus/libft_bonus.h"

char	*ft_strdup(const char *s1)
{
	int		str_len;
	char	*p;
	int		i;

	str_len = ft_strlen(s1);
	p = (char *)xmalloc((str_len + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
