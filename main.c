
# include "cub3D.h"

static t_list	*new_list(char *line)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content = line;
	new->next = NULL;
	return (new);
}

void		error_print(char *error)
{
//	int i;
	
//	i = 0;
	write(2, "Error\n", 6);
	while (*error)
		write(2, error++, 1);
}

int		error(int err)
{
	char	*error[5];

	error[0] = "Invalid quantity of arguments\n";
	error[1] = "Format of the 1-st argument is not '.cub'\n";
	error[2] = "Second argument is not '––save'\n";
	error[3] = "File can not open\n";
	error[4] = "Malloc problem\n";
	error_print(error[err]);
	return(-1);
}

int			main(int argc, char** argv)
{
	int		fd;
	char	*line;
	int		i;
	static	t_list	*head;
	t_list			*temp;

	if (argc < 2 || argc > 3)
		return(error(0));
	if ((i = ft_strlen(argv[1])) < 4)
		return (error(1));
	i -= 4;
	if ((ft_strncmp(argv[1] + i, ".cub", 5)) != 0)
		return (error(1));
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 7) != 0))
		return(error(2));
	if((fd = open(argv[1], O_APPEND)) == -1)
		return(error(3));
	get_next_line(fd, &line);
	if ((head = new_list(line)) == NULL)
		return (error(4));
	temp = head;
	while (get_next_line(fd, &line) == 1)
	{
		if ((temp->next = new_list(line)) == NULL)
			return (-1);
		temp = temp->next;
	}
	get_next_line(fd, &line);
	if ((temp->next = new_list(line)) == NULL)
		return (-1);
	temp = temp->next;
	temp = head;
	while (temp->next != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
	return (0);
}

