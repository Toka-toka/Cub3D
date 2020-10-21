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

void	colors_pars(char **line, int *color, t_settings *settings)
{
		int i;
		int	ii;
		char **new_line;

		if (line[1] == NULL || line[2] != NULL)
			error("Too much \\ less parametrs for color of floor \\ ceiling\n", settings);
		new_line = ft_split(line[1], ',');
		free_char_arr((void**)line);
		if (new_line[0] == NULL || new_line[1] == NULL || new_line[2] == NULL || new_line[3] != NULL)
			error("Too much \\ less parametrs for color of floor \\ ceiling\n", settings);
		i = 0;
		while(new_line[i] != NULL)
		{
			ii = 0;
			while(new_line[i][ii] != '\0')
			{
				if (new_line[i][ii] < '0' || new_line[i][ii] > '9')
					error("Wront symbols in color of floor \\ ceiling\n", settings);
				ii++;
			}
			i++;
		}
		i = 0;
		while (i < 3)
		{
			color[i] = ft_atoi(new_line[i]);
			if (color[i] < 0 || color[i] > 255)
				error("Incorrect color definition \\ ceiling\n", settings);
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
	
//    x = 5120;
//    y = 2880;
	if (settings->resol_x != -1 && settings->resol_y != -1)
		error("Double R\n", settings);
	if (line[3] != NULL || line[1] == NULL || line[2] == NULL)
		error("Too much \\ less parametrs for R\n", settings);
	i = 0;
	ii = 0;
	while (line[1][i] != '\0')
	{
		if (line[1][i] < '0' || line[1][i] > '9')
			error("Wrong simbols in R\n", settings);
		i++;
	}
	while (line[2][ii + 1] != '\0')
	{
		if  (line[2][ii] < '0' || line[2][ii] > '9')
			error("Wrong simbols in R\n", settings);
		ii++;
	}
	mlx_get_screen_size(settings->win->mlx, &x, &y);
	if ((settings->resol_x = ft_atoi(line[1])) > x || i > 5)
		settings->resol_x = x;
	if ((settings->resol_y = ft_atoi(line[2])) > y || ii > 5)
		settings->resol_y = y;
	if (settings->resol_x == 0 || settings->resol_y == 0)
		error("R_x or R_y = 0\n", settings);
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
		colors_pars(line, settings->color_f, settings);
	else if (ft_memcmp(line[0], "C", 2) == 0)
		colors_pars(line, settings->color_c, settings);
	else
		error("Invalid name or quantity of settings in file .cub\n", settings);
}

void	read_map(int fd, t_settings *settings, char *line)
{
	t_list *head;
	t_list *temp;
	int		i;
	int		len_max;

	i = 1;
	if ((head = new_list(line)) == NULL)
		error("Malloc problem (fn_read_map)", settings);
	len_max = ft_strlen(line);
	head->len = len_max;
	temp = head;
	while (get_next_line(fd, &line) == 1)
	{
		if ((temp->next = new_list(line)) == NULL)
			error("Malloc problem (fn_read_map)", settings);
		temp = temp->next;
		temp->len = ft_strlen(line);
		len_max = len_max > temp->len ? len_max : temp->len;
		i++;
	}
	temp->next = new_list(line);
	temp = temp->next;
	temp->len = ft_strlen(line);
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
	while (line[0] == '\0')
	{
		free(line);
		if (get_next_line(fd, &line) != 1)
			error("There is no map in file .cub?!\n", settings);
	}
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '1' || line[i] == ' ')
			i++;
		else
			error("Too many settings in file .cub", settings);
	}
	read_map(fd, settings, line);
	close(fd);
}
