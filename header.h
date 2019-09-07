#ifndef   HEADER_H
# define  HEADER_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

# define BUFF_SIZE 32
# define GNL_MACRO char buff[BUFF_SIZE]; char *ret; size_t size; size_t schr;

void	ft_strdel(char **as);
char	*char_remalloc(char *s, size_t n);
int		get_next_line(const int fd, char **line);
size_t  strichr(char *s, char c);
char    *ft_combine(char *sum, char *append);

#endif