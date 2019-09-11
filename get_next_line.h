#ifndef   GET_NEXT_LINE_H
# define  GET_NEXT_LINE_H

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include <stdlib.h>
# include <stdio.h>
# include "libft/libft.h"

# define BUFF_SIZE 1
# define GNL_MACRO char buff[BUFF_SIZE]; char *ret; size_t size; size_t schr;
# define MAX_FD 65535

typedef struct		s_node
{
	char			*s;
	struct s_node	*next;
}					node;

int				get_next_line(const int fd, char **line);

#endif