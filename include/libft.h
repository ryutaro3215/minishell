#ifndef LIBFT_H
# define LIBFT_H

# include "xmalloc.h"

# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

// libft
size_t	ft_strlen(const char *s);
bool	ft_isalpha(int c);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, size_t n);
char	*strjoin_but_freed_only_first_arg(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

// ft_printf.c
int	ft_printf(const char *str, ...);
int	if_char(va_list ap);
int	if_char_p(va_list ap);
int	if_void_p(va_list ap);
int	if_decimal(va_list ap);
int	if_unsigned_decimal(va_list ap);
int	if_hexadec_low(va_list ap);
int	if_hexadec_up(va_list ap);
int	ft_put_int(int n, int *p);
int	ft_put_unsigned_int(unsigned int n, int *p);
int	ft_put_address(uintptr_t n, int *p);
int	ft_put_hexadec_low(unsigned int n, int *p);
int	ft_put_hexadec_up(unsigned int n, int *p);

#endif
