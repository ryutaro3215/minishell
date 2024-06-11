#include "../include_bonus/libft_bonus.h"

char	*strjoin_but_freed_only_first_arg(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	s3 = xmalloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	return (s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;
	char	*tmp;

	if (!s1)
	{
		tmp = ft_strdup(s2);
		free(s2);
		return (tmp); // valid in every use ?
	}
	s3 = xmalloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s3 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		s3[i++] = s1[j++];
	j = 0;
	while (s2[j])
		s3[i++] = s2[j++];
	s3[i] = '\0';
	free(s1);
	free(s2);
	return (s3);
}
