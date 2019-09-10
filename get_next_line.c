#include "header.h"

/*
**	this program
*/

typedef struct
{
	char	*s;
	node	*next;
}			node;

//allocate for list
static node	*createlst(node *ptr)
{
	if (!ptr)
		if (!(ptr = (node *)malloc(sizeof(node))))
			return (NULL);
	return (ptr);
}

// converting string to list
static void	strtolist(char *tmp, node *ptr)
{
	size_t	i;
	char	*start;
	node	*new;

	start = tmp;
	ptr = createlst(ptr);
	while (*tmp)
	{
		i = strichr(tmp, '\n');
		ptr->s = ft_strsub(tmp, 0, i - 1);
		(i + 1 <= strlen(tmp)) ? tmp += i + 1 : 0;
		new = createlst(new);
		ptr->next = new;
		new = NULL;
	}
	free(start);	//hopefully this will free it
}

//this should dequeue
static node	*dequeue(char **line, node *head)
{
	node *ptr;

	ptr = head->next;
	*line = head->s;
	free(head);
	return (ptr);
}

int		get_next_line(int fd, char **line)
{
	static node *heads[MAX_FD];
	char		buff[BUFF_SIZE];
	char		*tmp;
	size_t		size;
	
	if (fd < 0 || fd > MAXFD || !line || (read(fd, 0, 0) < 0))
		return (-1);
	if (!(tmp = (char *)malloc(sizeof(char) * (1))))
		return (-1);
	ft_bzero(tmp, 1);
	if (!heads[fd])
	{
		//taking the whole string.
		while ((size = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[size] = '\0';
			tmp = ft_combine(tmp, buff);
			ft_bzero(buff, BUFF_SIZE);
			if (size == 0)
				break;
		}
	//function to separate into linked list
		strtolist(tmp, heads[65353]);
		dequeue(line, heads[fd]);
	}
	heads[fd] = dequeue(line, heads[fd]);
	return (heads[fd]->next == NULL ? 0 : 1);
}

int main(int argc, char **argv)
{
    char *line;    
    int fd;

    fd = open(argv[1], O_RDONLY);
    if ((get_next_line(fd, &line) > 0))
    {
        printf("%s\n", line);
        free(line);
    }
    return (1);
}
