/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vilee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 21:52:06 by vilee             #+#    #+#             */
/*   Updated: 2019/09/13 21:52:35 by vilee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	This function should return 3 things
**		1.)	if '\n', return 1;
**		2.) if EOF, return 0;
**		3.) if error, return -1;
*/

static size_t	strichr(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void		ft_combine(char **tmp, char *buff)
{
	char	*del;

	del = *tmp;
	*tmp = ft_strjoin(*tmp, buff);
	free(del);
}

static int		reject_line(int size, char **line, char **tmp, char **s)
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

int				get_next_line(int fd, char **line)
{
	static char *s[MAX_FD];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			size;

	size = 1;
	if (fd < 0 || fd > MAX_FD || !line || (read(fd, 0, 0) < 0))
		return (-1);
	tmp = ft_strdup("");
	s[fd] ? ft_combine(&tmp, s[fd]) : 0;
	s[fd] ? free(s[fd]) : 0;
	if (strichr(tmp, '\n') < ft_strlen(tmp))
		return (reject_line(size, line, &tmp, &s[fd]));
	while ((size = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[size] = '\0';
		ft_combine(&tmp, buff);
		if (strichr(buff, '\n') < ft_strlen(buff))
			break ;
	}
	if (!s[fd])
		return (reject_line(1, line, &tmp, &s[fd]));
	(ft_strcmp(tmp, "")) ? size++ : 0;//free(tmp) : 0;
	return (reject_line(size, line, &tmp, &s[fd]));
}
/*
int main(int argc, char **argv)
{
    char *line;
    int fd;

    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s\n", line);
        free(line);
    }
    return (0);
}
*/