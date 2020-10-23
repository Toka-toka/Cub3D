/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_settings.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:36:42 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:36:45 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	pars_settings(t_settings *settings, char *line, char sym1, char sym2)
{
	if (sym1 == 'R')
		resolution_pars(ft_split(line, ' '), settings);
	else if (sym1 == 'E' && sym2 == 'A')
		load_textures(settings, &settings->xpm[0], line, 0);
	else if (sym1 == 'N' && sym2 == 'O')
		load_textures(settings, &settings->xpm[1], line, 1);
	else if (sym1 == 'W' && sym2 == 'E')
		load_textures(settings, &settings->xpm[2], line, 2);
	else if (sym1 == 'S' && sym2 == 'O')
		load_textures(settings, &settings->xpm[3], line, 3);
	else if (sym1 == 'S')
		load_textures(settings, &settings->xpm[4], line, 4);
	else if (sym1 == 'F')
		colors_pars(ft_split(line, ','), settings->color_f, settings);
	else if (sym1 == 'C')
		colors_pars(ft_split(line, ','), settings->color_c, settings);
	else
		error("Invalid name or quantity of settings in file .cub\n", settings);
}

void	skip_spaces(t_settings *settings, char *line, int i)
{
	char symbol1;
	char symbol2;

	while (*line == ' ')
		line++;
	symbol1 = line[0];
	line[0] = ' ';
	symbol2 = line[1];
	line[1] = ' ';
	while (*line == ' ')
		line++;
	pars_settings(settings, line, symbol1, symbol2);
}

void	read_settings(int fd, t_settings *settings)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(fd, &line) == 1 && i < 8)
	{
		if (line[0] != '\0')
			skip_spaces(settings, line, i++);
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
}