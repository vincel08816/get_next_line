#include "get_next_line.h"

/*
**	This function should return 3 things
**		1.)	if '\n', return 1;
**		2.) if EOF, return 0;
**		3.) if error, return -1;
*/

static int strichr(char *s, char c)
{
	int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	ft_combine(char **tmp, char *buff)
{
	char	*del;

	del = *tmp;
	*tmp = ft_strjoin(*tmp, buff);
	free(del);
}

static int	reject_line(int size, char **line, char **tmp, char **s)
{
	size_t	i;
	char	*start;
	
	if (!size)
		return (0);
	i = 0;
	start = *tmp;
	i = strichr(*tmp, '\n');
	*line = ft_strsub(*tmp, 0, i);
	*tmp += i + 1;
	if (**tmp != '\0' || **tmp != '\n') 
		*s = ft_strdup(*tmp);
	free(start);
	return (1);
}

/*
int		main(void)
{
	char *tmp = ft_strdup("as\ndfa\nsd\n\n\nfasdfasdfa\nsd\nfasd\nfasdfa\nsdf");
	char *line = NULL;
	char *s = NULL;
	
	while (eject_line((int)ft_strlen(tmp), &line, &tmp, &s))
	{
		printf("%s\n", line);
		free(line);
		tmp = s;
		//ft_strdel(&s);
	}
	return (0);
}*/

int		get_next_line(int fd, char **line)
{
	static char *s[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			size;
	int reject;
	
	size = 1;
	if (fd < 0 || fd > MAX_FD || !line || (read(fd, 0, 0) < 0))
		return (-1);
	tmp = ft_strdup("");
	s[fd] ? ft_combine(&tmp, s[fd]) : 0;
	s[fd] ? free(s[fd]) : 0;
	if (strichr(tmp, '\n') < (int)ft_strlen(tmp))
		return (reject_line(size, line, &tmp, &s[fd]));
	while ((size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[size] = '\0';
		ft_combine(&tmp, buff);
		if (strichr(buff, '\n') < (int)ft_strlen(buff))
			break;
	}
	if (!s[fd])
		return (reject_line(1, line, &tmp, &s[fd]));
	(size == 0) ? free(s[fd]) : 0;
	(size == 0) ? free(tmp) : 0;
	reject = reject_line(size, line, &tmp, &s[fd]);
	return (reject);
}

int main(int argc, char **argv)
{
	char *line;
	int fd;
	//int fd2;
	int i = 0;
	
	if (argc)
		i = 0;
	fd = open(argv[1], O_RDONLY);
	//fd2 = open(argv[2], O_WRONLY);
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		printf("%s\n", line);
		//write(fd2, &line, 1);
		//write(fd2, "\n", 1);
		free(line);
	}
	printf("%d\n", i);
	return (0);
}
