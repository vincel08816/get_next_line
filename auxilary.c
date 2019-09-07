#include "header.h"

void	ft_strdel(char **as)
{
	if (*as)
	{
		free(*as);
		*as = NULL;
	}
}

/*
**  remalloc is just a bad version of realloc
**  why isn't it freeing T_T  oh..... string literal lol
*/

char	*char_remalloc(char *s, size_t n)
{
	char *ptr;

	if (!(s) || !n)
		return (NULL);
	//ptr = ft_strnew(n);
	ptr = (char *)malloc(sizeof(char) * n + 1);
	bzero(ptr, n + 1);
	
	ptr = strncat(ptr, s, n);
	//free(s);
	ft_strdel(&s);
	return (ptr);
}

/*	my super strjoin :D
allocates, appends, then frees old string.	
it's a godly function
*/

char    *ft_combine(char *sum, char *append)
{
    size_t len; // len of the whole new string

    // in the case that the string append string is larger
    len = strlen(sum) + strlen(append);
    //printf ("%zu\n", len);
    sum = char_remalloc(sum, len);
    len = strlen(append);
    strncat(sum, append, len);
    //printf("%s", sum);
    return (&sum[0]);
}

size_t  strichr(char *s, char c)
{
	size_t i = 0;

	if (!s)
		return (0);
	while(s[i] != c && s[i])
		i++;
	return (i);
}

/* 
**this main is for testing my string char
int main(void)
{
  char *s;
  
  s = (char *)malloc(sizeof(char) * (6 + 1));
  s = strcpy(s, "123abc");    //string literal
  s = char_remalloc(s, 9);
  s = strncat(s, "dea", 3);   //seems like this works like
  printf("%lu\n" , strlen(s));
  printf("%s", s);
}
*/

