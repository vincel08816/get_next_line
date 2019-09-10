#include "libft.h"

size_t  strichr(char *s, char c)
{
	size_t i = 0;

	if (!s)
		return (0);
	while(s[i] != c && s[i])
		i++;
	return (i);
}