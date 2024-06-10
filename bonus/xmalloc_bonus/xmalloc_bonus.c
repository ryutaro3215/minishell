# include "../include_bonus/xmalloc_bonus.h"

void	*xmalloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	handle_error(!ptr && errno == ENOMEM);
	return (ptr);
}
