#include "../include_bonus/libft_bonus.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		str_len;
	char	*str_finded;
	char	c_conv;

	c_conv = c;
	i = 0;
	str_len = ft_strlen(s);
	while (i <= str_len)
	{
		if (s[i] == c_conv)
		{
			str_finded = (char *)&s[i];
			return (str_finded);
		}
		i++;
	}
	return (NULL);
}
