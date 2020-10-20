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

void	colors_pars(char **line, int *color) // TODO: перевести цвет в инт по битам
{
		int i;
		int	ii;
		char **new_line;

		printf("color[%d] = %s\n", 0, line[1]);
		if (line[1] == NULL || line[2] != NULL)
			error("Too much \\ less parametrs for color of floor \\ ceiling\n");
		new_line = ft_split(line[1], ',');
		free_char_arr((void**)line);
		if (new_line[0] == NULL || new_line[1] == NULL || new_line[2] == NULL || new_line[3] != NULL)
			error("Too much \\ less parametrs for color of floor \\ ceiling\n");
		i = 0;
		while(new_line[i] != NULL)
		{
			ii = 0;
			while(new_line[i][ii] != '\0')
			{
				if (new_line[i][ii] < '0' || new_line[i][ii] > '9')
					error("Wront symbols in color of floor \\ ceiling\n");
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
				error("Incorrect color definition \\ ceiling\n");
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

void	resolution_pars(char **line, t_settings *settings)
{
	int i;
	int ii;
	int x;
	int y;
	
    x = 5120;
    y = 2880;
	if (settings->resol_x != -1 && settings->resol_y != -1)
		error("Double R\n");
	if (line[3] != NULL || line[1] == NULL || line[2] == NULL)
		error("Too much \\ less parametrs for R\n");
	i = 0;
	ii = 0;
	while (line[1][i] != '\0')
	{
		if (line[1][i] < '0' || line[1][i] > '9')
			error("Wrong simbols in R\n");
		i++;
	}
	while (line[2][ii + 1] != '\0')
	{
		if  (line[2][ii] < '0' || line[2][ii] > '9')
			error("Wrong simbols in R\n");
		ii++;
	}
	mlx_get_screen_size(settings->win->mlx, &x, &y);
	if ((settings->resol_x = ft_atoi(line[1])) > x || i > 5)
		settings->resol_x = x;
	if ((settings->resol_y = ft_atoi(line[2])) > y || ii > 5)
		settings->resol_y = y;
	if (settings->resol_x == 0 || settings->resol_y == 0)
		error("Wrong simbols in R\n");
	free_char_arr((void**)line);
}

void		pars_settings(char **line, t_settings *settings)
{
	if (ft_memcmp(line[0], "R", 2) == 0)
		resolution_pars(line, settings);
	else if (ft_memcmp(line[0], "EA", 3) == 0)
		load_textures(settings, &settings->xpm[0], line, 0);
	else if (ft_memcmp(line[0], "NO", 3) == 0)
		load_textures(settings, &settings->xpm[1], line, 1);
	else if (ft_memcmp(line[0], "WE", 3) == 0)
		load_textures(settings, &settings->xpm[2], line, 2);
	else if (ft_memcmp(line[0], "SO", 3) == 0)
		load_textures(settings, &settings->xpm[3], line, 3);
	else if (ft_memcmp(line[0], "S", 2) == 0)
		load_textures(settings, &settings->xpm[4], line, 4);
	else if (ft_memcmp(line[0], "F", 2) == 0)
		colors_pars(line, settings->color_f);
	else if (ft_memcmp(line[0], "C", 2) == 0)
		colors_pars(line, settings->color_c);
	else
		error("Invalid name or quantity of settings in file .cub\n");
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

void	map_chek(char **map, int i, int ii, t_settings *settings) // TODO: огромная функция!!!))
{
	while(map[i + 1] != NULL)
	{
		ii = 0;
		while (map[i][ii] == ' ')
			ii++;
		if (map[i][ii] == '0')
		{
			printf("Error here 1");
			error("The map is not closed\n");
		}
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] == '1' || map[i][ii] == ' ')
				ii++;
			else if (map[i][ii] == '2')
			{
				new_sprite(i, ii, settings);
//				map[i][ii] = '0';
				ii++;
			}
			else if (map[i][ii] == '0') 
			{
				if (map[i + 1][ii] == '\0' || map[i + 1][ii] == ' ')
				{
					printf("Error here 2");
					error("The map is not closed\n");
				}
				if (map[i - 1][ii] == '\0' || map[i - 1][ii] == ' ')
				{
					printf("Error here 3");
					error("The map is not closed\n");
				}
				if (map[i][ii + 1] == '\0' || map[i][ii + 1] == ' ')
				{
					printf("Error here 4");
					error("The map is not closed\n");
				}
				if (map[i][ii - 1] == '\0' || map[i][ii - 1] == ' ')
				{
					printf("Error here 5");
					error("The map is not closed\n");
				}
				ii++;
			}
			else if (map[i][ii] == 'N' || map[i][ii] == 'S' || map[i][ii] == 'E' || map[i][ii] == 'W')
			{
				if (settings->plr->pov != 0)
					error("Double camera plase\n");
				settings->plr->x = ii * CBSZ + CBSZ / 2;
				settings->plr->y = i * CBSZ + CBSZ / 2;
				if (map[i][ii] == 'N')
					settings->plr->pov = M_PI / 2;
				if (map[i][ii] == 'S')
					settings->plr->pov = M_PI * 3 / 2;
				if (map[i][ii] == 'E')
					settings->plr->pov = 2 * M_PI;
				if (map[i][ii] == 'W')
					settings->plr->pov = M_PI;
				map[i][ii] = '0';
				ii++;
			}
			else error("Invalid symbol in map\n");
		}
		i++;
	}
	if (settings->plr->pov == 0)
		error("No camera plase\n");
}

void	pars_map(t_settings *settings, int len_max, int lists, t_list *head)
{
	int i;


	t_list *temp;
	printf("lists = %d", lists);
	settings->map = (char**)malloc((lists + 1) * sizeof(char *));
	i = 0;
	while (i < lists)
	{
		printf("i = %d, list = %d\n", i, lists);
		printf("This line = %s\n", head->content);
		if (head->content[head->len - 1] != '1' || head->content[0] == '0')
		{
			printf("Error here 6");				
			error("The map is not closed\n");
		}
		settings->map[i] = (char*)ft_calloc((len_max + 1), sizeof(char ));
		settings->map[i] = ft_memcpy(settings->map[i], head->content, head->len);
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
		i++;
	}
	settings->max_x = len_max - 1;
	settings->max_y = lists - 1; // TODO: проверить значения
	len_max = 0;
	while (settings->map[i - 1][len_max] != '\0')
	{
		if (settings->map[i - 1][len_max] == '1' || settings->map[i - 1][len_max] == ' ')
			len_max++;
		else
			error("The last line of a map is invalid\n");
	}
	settings->map[i] = NULL;
	i = 0;
	while (settings->map[i] != NULL)
	{
		printf("\nmap[%d] = %s", i, settings->map[i]);
		i++;
	}
	map_chek(settings->map, 1, 0, settings);
}

void	read_map(int fd, t_settings *settings, char *line)
{
	t_list *head;
	t_list *temp;
	int		i;
	int		len_max;

	i = 1;
//	printf("%s\n", *line);
	if ((head = new_list(line)) == NULL)
		error("Malloc problem (fn_read_map)");
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
			error("Malloc problem (fn_read_map)");
		temp = temp->next;
		temp->len = ft_strlen(line);
		len_max = len_max > temp->len ? len_max : temp->len;
		i++;
//		free(*line);
	}
	temp->next = new_list(line);
	temp = temp->next;
	temp->len = ft_strlen(line);
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
    int     i;
	
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
			error("There is no map in file .cub?!\n");
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			error("Too many settings in file .cub");
	}
	read_map(fd, settings, line);
	close(fd);
}
