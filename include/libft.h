#ifndef LIBFT_H
#define LIBFT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char	*strjoin_but_freed_only_first_arg(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
