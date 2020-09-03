# include "../includes/cub3D.h"

static t_list	*new_list(char *line)
{
	t_list	*new;

	if (!(new = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	new->content = line;
	new->next = NULL;
	return (new);
}

void	colors_pars(char **line, int *color)
{
		int i;
		int	ii;
		char **new_line;

		printf("color[%d] = %s\n", 0, line[1]);
		if (line[1] == NULL || line[2] != NULL)
			error(20);
		new_line = ft_split(line[1], ',');
		free_char_arr((void**)line);
		if (new_line[0] == NULL || new_line[1] == NULL || new_line[2] == NULL || new_line[3] != NULL)
			error(20);
		i = 0;
		while(new_line[i] != NULL)
		{
			ii = 0;
			while(new_line[i][ii] != '\0')
			{
				if (new_line[i][ii] < '0' || new_line[i][ii] > '9')
					error(21);
				ii++;
			}
			i++;
		}
		i = 0;
		while (i < 3)
		{
			color[i] = ft_atoi(new_line[i]);
			printf("color[%d] = %d\n", i, color[i]);
			if (color[i] < 0 || color[i] > 255)
				error(22);
			i++;
		}
		i = 0;
		while (new_line[i] != NULL)
		{
			printf("color[%d] = %s", i, new_line[i]);
			i++;
		}
		free_char_arr((void**)new_line);
}

void	path_pars(char **line, char **way)
{
		int fd;
		char *temp;
//		printf("way = %s", *way);
		if (*way != NULL)
			error(19);
		if (line[1] == NULL || line[2] != NULL || (fd = open(line[1], O_APPEND)) == -1)
			error(18);
		*way = line[1];
		line[1] = ft_strdup("");
		free_char_arr((void**)line);
}

void	resolution_pars(char **line, t_settings *settings)
{
	int i;
	
	i = 0;
	if (settings->resol_x != -1 && settings->resol_y != -1)
		error(8);
	if (line[3] != NULL || line[1] == NULL || line[2] == NULL)
		error(9);
	while (line[1][i] != '\0')
	{
		if (line[1][i] < '0' || line[1][i] > '9')
			error(10);
		i++;
	}
	settings->resol_x = ft_atoi(line[1]);
	settings->resol_y = ft_atoi(line[2]);

	while(line[i] != NULL)
	{
		printf("\nline[i] = %s\n", line[i]);
		i++;
	}
	printf("\nresol = %d\n", settings->resol_x);
	printf("\nresol = %d\n", settings->resol_y);
	free_char_arr((void**)line);
}

void		pars_settings(char **line, t_settings *settings)
{
  	int i;

	if (ft_memcmp(line[0], "R", 2) == 0)
		resolution_pars(line, settings);
	else if (ft_memcmp(line[0], "NO", 3) == 0)
		path_pars(line, &settings->path_no);
	else if (ft_memcmp(line[0], "SO", 3) == 0)
		path_pars(line, &settings->path_so);
	else if (ft_memcmp(line[0], "WE", 3) == 0)
		path_pars(line, &settings->path_we);
	else if (ft_memcmp(line[0], "EA", 3) == 0)
		path_pars(line, &settings->path_ea);
	else if (ft_memcmp(line[0], "S", 2) == 0)
		path_pars(line, &settings->path_s);
	else if (ft_memcmp(line[0], "F", 2) == 0)
		colors_pars(line, settings->color_f);
	else if (ft_memcmp(line[0], "C", 2) == 0)
		colors_pars(line, settings->color_c);
	else
		error(6);
	i = 0;
//	while(line[i] != NULL)
//	{
//		free(line[i]);
//		i++;
//	}
//	free(line[0]);
//	free(**line);
}

/*	int		iii; 
	static	t_list	*head;
	t_list			*temp;
	char	**split;
	char	color[12]; */
void	map_chek(char **map, int i, int ii, char *flag)
{
	while(map[i + 1] != NULL)
	{
		ii = 0;
		while (map[i][ii] == ' ')
			ii++;
		if (map[i][ii] == '0')
		{
			printf("Error here 1");
			error(13);
		}
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] == '1' || map[i][ii] == '2' || map[i][ii] == ' ')
				ii++;
			else if (map[i][ii] == '0') 
			{
				if (map[i + 1][ii] == '\0' || map[i + 1][ii] == ' ')
				{
					printf("Error here 2");
					error(13);
				}
				if (map[i - 1][ii] == '\0' || map[i - 1][ii] == ' ')
				{
					printf("Error here 3");
					error(13);
				}
				if (map[i][ii + 1] == '\0' || map[i][ii + 1] == ' ')
				{
					printf("Error here 4");
					error(13);
				}
				if (map[i][ii - 1] == '\0' || map[i][ii - 1] == ' ')
				{
					printf("Error here 5");
					error(13);
				}
				ii++;
			}
			else if (map[i][ii] == 'N' || map[i][ii] == 'S' || map[i][ii] == 'E' || map[i][ii] == 'W')
			{
				*flag == 0 ? *flag = map[i][ii] : error(16);
				ii++;
			}
			else error(15);
		}
		i++;
	}
	if (flag == 0)
		error(17);
}

void	pars_map(t_settings *settings, int len_max, int lists, t_list *head)
{
	int i;

	t_list *temp;
	printf("lists = %d", lists);
	settings->map = (char**)malloc((lists +1) * sizeof(char *));
	i = 0;
	while (i < lists)
	{
		if (head->content[head->len - 1] != '1' || head->content[0] == '0')
			error(13);
		settings->map[i] = (char*)ft_calloc((len_max + 1), sizeof(char ));
		settings->map[i] = ft_memcpy(settings->map[i], head->content, head->len);
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
		i++;
	}
	len_max = 0;
	while (settings->map[i - 1][len_max] != '\0')
	{
		if (settings->map[i - 1][len_max] == '1' || settings->map[i - 1][len_max] == ' ')
			len_max++;
		else
			error(14);
	}
	settings->map[i] = NULL;
	i = 0;
	while (settings->map[i] != NULL)
	{
		printf("\nmap[%d] = %s", i, settings->map[i]);
		i++;
	}
	map_chek(settings->map, 1, 0, &settings->orientation_flag);
}

void	read_map(int fd, t_settings *settings, char *line)
{
	t_list *head;
	t_list *temp;
	char	*line1;
	int		i;
	int		len;
	int		len_max;

	i = 1;
//	printf("%s\n", *line);
	if ((head = new_list(line)) == NULL)
		error(12);
	len_max = ft_strlen(line);
	head->len = len_max;
	printf("head->len = %d\n", head->len);
//	free(*line);
	temp = head;
//	temp->next = new_list(line);
//	temp = temp->next;
//	get_next_line(fd, &line1);
//	temp->next = new_list(line);
//	temp = temp->next;
//	printf("%s\n", temp->content);
//	printf("%d\n", fd);
//	printf("%s\n", line);
//	printf("%d\n", get_next_line(fd, &line));
//	temp->next = new_list(line);
	//	error(12);
//	temp = temp->next;
//	printf("%s\n", temp->content);
	while (get_next_line(fd, &line) == 1)
	{
//		printf("%s\n", *line);
		if ((temp->next = new_list(line)) == NULL)
			error(12);
		temp = temp->next;
		temp->len = ft_strlen(line);
		len_max = len_max > temp->len ? len_max : temp->len;
		i++;
//		free(*line);
	}
	temp->next = new_list(line);
	temp = temp->next;
	temp->len = ft_strlen(line);
	i++;
	printf("len_max = %d\ni = %d\n", len_max, i);
//	printf("%s\n", *line);
//	if ((temp->next = new_list(*line)) == NULL)
//		error(12);
//	free(*line);
	temp = head;
	while (temp->next != NULL)
	{
		if (temp->content[0] == '\0')
			printf("Empty line\n");
		printf("%s\n", temp->content);
		printf("%d\n", temp->len);
		temp = temp->next;
	}
	printf("%s\n", temp->content);
	printf("%d\n", temp->len);
	close(fd);
	pars_map(settings, len_max, i, head);
}

void	read_settings(int fd, t_settings *settings)
{
    char    *line;
	char	*line1;
    int     i;
	t_list *head;
	t_list *temp;
	
	i = 0;
    while (get_next_line(fd, &line) == 1 && i < 8)
	{
		if (line[0] != '\0')
		{
			pars_settings(ft_split(line, ' '), settings);
			i++;
		}
		free(line);
	}
	printf("%d\n", i);
	while (line[0] == '\0')
	{
		free(line);
		if (get_next_line(fd, &line) != 1)
			error(11);
	}
	i = 0;
//	while (get_next_line(fd, &line) == 1)
//		printf("%s\n", line);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			error(7);
	}
//	get_next_line(fd, &line);
//	printf("%s\n", line);
	read_map(fd, settings, line);
//	if ((head = new_list(line)) == NULL)
//		error(12);
//	temp = head;
//	printf("%s\n", temp->content);
//	get_next_line(fd, &line1);
//	temp->next = new_list(line);
//	temp = temp->next;
//	
//	temp->next = new_list(line);
//	temp = temp->next;
//	printf("%d\n", fd);
	close(fd);
}