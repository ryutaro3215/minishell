#include "../include_bonus/libft_bonus.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d_len;

	if ((dst == NULL && dstsize == 0) || (dstsize <= ft_strlen(dst)))
		return (dstsize + ft_strlen(src));
	i = ft_strlen(dst);
	d_len = ft_strlen(dst);
	j = 0;
	while (src[j] && i < dstsize - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (d_len + ft_strlen(src));
}
