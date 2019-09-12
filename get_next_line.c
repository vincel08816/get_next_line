#include "get_next_line.h"

/*
**	This function should return 3 things
**		1.)	if '\n', return 1;
**		2.) if EOF, return 0;
**		3.) if error, return -1;
*/

//allocate for list
static node	*createlst(node *ptr)
{
	if(!(ptr = (node*)malloc(sizeof(node))))
		return (NULL);
	ptr->next = NULL;
	return (ptr);
}

/*
**	converting string to list
**	frees string after the program is run
*/
static void	strtolist(char *tmp, node **head)
{
	size_t	i;
	char	*start;
	node	*new;
	node	*now;

	start = tmp;
	*head = createlst(*head);
	now = *head;
	while (*tmp)
	{
		i = strichr(tmp, '\n');
		now->s = ft_strsub(tmp, 0, i);
		//printf("%s", now->s);
		(i + 1 <= ft_strlen(tmp)) ? tmp += i + 1 : 0;
		new = createlst(new);
		now->next = new;
		now = now->next;
		new = NULL;
	}
	free(start);	//hopefully this will free it
}

//this should dequeue
static void	dequeue(char **line, node **head)
{
	node *ptr;

	ptr = *head;
	*line = (*head)->s;
	*head = (*head)->next;
	free(ptr);
}
/*
int		main(void)
{
	char	*test_string = ft_strdup("asdn\nlkj\nasd;lfkja;l\n\nskdjf\n");
	node	*ptr;

	ptr = NULL;
	//printf("test_string: %s", test_string);
	strtolist(test_string, ptr);

	while (ptr)
	{
		printf("%s\n", ptr->s);
		ptr = ptr->next;
	}
	return (0);
}
*/

int		get_next_line(int fd, char **line)
{
	static node *heads[MAX_FD];
	char		buff[BUFF_SIZE];
	char		*tmp;
	int			size;
	
	size = -42;
	if (fd < 0 || fd > MAX_FD || !line || (read(fd, 0, 0) < 0))
		return (-1);
	tmp = ft_strdup("");
	if (!heads[fd])
	{
		while ((size = read(fd, buff, BUFF_SIZE)) > 0)
		{
			buff[size] = '\0';
			tmp = ft_combine(tmp, buff);
			ft_bzero(buff, BUFF_SIZE);
		}
		strtolist(tmp, &heads[fd]);
	}
	(size == -42) ? free(tmp): 0;
	heads[fd] ? dequeue(line, &heads[fd]) : 0;
	return (!heads[fd] ? 0 : 1);
}

/*void	printlst(node *ptr)
{
	while (ptr)
	{
		printf("%s", ptr->s);
		ptr = ptr->next;
	}
}*/
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