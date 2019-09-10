#ifndef   HEADER_H
# define  HEADER_H

# include "fcntl.h"
# include "sys/types.h"
# include "sys/uio.h"
# include "unistd.h"
# include "stdlib.h"
# include "libft/libft.h"

# define BUFF_SIZE 1
# define GNL_MACRO char buff[BUFF_SIZE]; char *ret; size_t size; size_t schr;
# define MAX_FD 65535

int		get_next_line(const int fd, char **line);



#endif