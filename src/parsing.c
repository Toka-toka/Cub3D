#include "../includes/cub3D.h"

void	colors_pars(char **l, int *color, t_settings *settings)
{
	int		i;
	int		ii;

	if (l[0] == NULL || l[1] == NULL || l[2] == NULL || l[3] != NULL)
		error("Wrong parametrs for color of floor \\ ceiling\n", settings);
	i = 0;
	while (i < 3)
	{
		ii = 0;
		while (l[i][ii] != '\0')
		{
			if (l[i][ii] < '0' || l[i][ii] > '9')
				error("Wront symbols in color of floor \\ ceiling\n", settings);
			ii++;
		}
		color[i] = ft_atoi(l[i]);
		if (color[i] < 0 || color[i] > 255)
			error("Incorrect color definition \\ ceiling\n", settings);
		i++;
	}
	color[0] = 0 << 24 | color[0] << 16 | color[1] << 8 | color[2];
}

void	resolution_pars(char **line, t_settings *settings)
{
	int		i;
	int		ii;
	int		x;
	int		y;

	if (settings->resol_x != -1 && settings->resol_y != -1)
		error("Double R\n", settings);
	if (line[0] == NULL || line[1] == NULL || line[2] != NULL)
		error("Too much \\ less parametrs for R\n", settings);
	i = 0;
	ii = 0;
	while (line[0][i] != '\0')
		if (line[0][i] < '0' || line[0][i++] > '9')
			error("Wrong simbols in R\n", settings);
	while (line[1][ii] != '\0')
		if (line[1][ii] < '0' || line[1][ii++] > '9')
			error("Wrong simbols in R\n", settings);
	if (line[0][0] == '0' || line[1][0] == '0')
		error("R_x or R_y = 0\n", settings);
	mlx_get_screen_size(settings->win->mlx, &x, &y);
	if ((settings->resol_x = ft_atoi(line[0])) > x || i > 5)
		settings->resol_x = x;
	if ((settings->resol_y = ft_atoi(line[1])) > y || ii > 5)
		settings->resol_y = y;
	free_char_arr((void**)line);
}

void	pars_settings(t_settings *settings, char *line)
{
	int		i;
	char	symbol1;
	char	symbol2;

	i = 0;
	while (*line == ' ')
		line++;
	symbol1 = line[0];
	line[0] = ' ';
	symbol2 = line[1];
	line[1] = ' ';
	while (line[i] == ' ')
		i++;
	if (symbol1 == 'R')
		resolution_pars(ft_split(line + i, ' '), settings);
	else if (symbol1 == 'E' && symbol2 == 'A')
		load_textures(settings, &settings->xpm[0], line + i, 0);
	else if (symbol1 == 'N' && symbol2 == 'O')
		load_textures(settings, &settings->xpm[1], line + i, 1);
	else if (symbol1 == 'W' && symbol2 == 'E')
		load_textures(settings, &settings->xpm[2], line + i, 2);
	else if (symbol1 == 'S' && symbol2 == 'O')
		load_textures(settings, &settings->xpm[3], line + i, 3);
	else if (symbol1 == 'S')
		load_textures(settings, &settings->xpm[4], line + i, 4);
	else if (symbol1 == 'F')
		colors_pars(ft_split(line + i, ','), settings->color_f, settings);
	else if (symbol1 == 'C')
		colors_pars(ft_split(line + i, ','), settings->color_c, settings);
	else
		error("Invalid name or quantity of settings in file .cub\n", settings);
}

void	read_map(int fd, t_settings *settings, char *line)
{
	t_list	*head;
	t_list	*temp;
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
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < 8)
	{
		if (line[0] != '\0')
		{
			pars_settings(settings, line);
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
