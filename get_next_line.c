#include "header.h"

int		get_next_line(const int fd, char **line)
{
	static char	*fds[65535];		//this is a potential failure
	char		buff[BUFF_SIZE];
	char		*tmp;				//second point of allocation
	size_t		size;
	size_t		sc;

	if (fd < 0 || fd > 65535 || !line || (read(fd, 0, 0) < 0))
		return (-1);
	size = 0;
	sc = 0;

	//allocating memory and setting end to null (strnew)
	if (!(tmp = (char *)malloc(sizeof(char) * (1))))
		return (-1);
	bzero(tmp, 1);
	if (fds[fd])
	{
		printf("%s", fds[fd]);
		tmp = ft_combine(tmp, fds[fd]);
		free(fds[fd]);
	}
	//read until 
	while ((size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		//printf("%zu", size);
		buff[size] = '\0';
		// break when strchr does not point to the end of the string
		if (strichr(buff, '\0') != strichr(buff, '\n'))
			break;
		tmp = ft_combine(tmp, buff);
	}
	(strichr(buff, '\0') > strichr(buff, '\n')) ? sc = strichr(buff, '\n') : \
	(sc = strichr(buff, '\0'));
	fds[fd] = strdup(&buff[sc + 1]);
	//printf("%zu", sc);
	tmp = char_remalloc(tmp, strlen(tmp) + sc);
	tmp = strncat(tmp, buff, sc);
	*line = tmp;
	strichr(buff, '\0') < strichr(buff, '\n') ? ft_strdel(&fds[fd]) : 0;
	return (strichr(buff, '\0') > strichr(buff, '\n') ? 1 : 0);
}

int main(int argc, char **argv)
{
    char *line;    
    int fd;

    fd = open(argv[1], O_RDONLY);
    while ((get_next_line(fd, &line) > 0))
    {
        printf("%s\n", line);
        free(line);
		//ft_strdel(&line);
    }
	//free(line);
    return (0);
}
