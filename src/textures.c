# include "../includes/cub3D.h"
/*
int			open_xpm(t_settings *settings, t_xpm *xpm)
{
	int i;
	int ii;
	int iii;
	int *addr;

	// TODO: попробовать открыть файл
	xpm->addr = (int**)malloc(CBSZ * sizeof(int *));
	i = 0;
	while (i < CBSZ)
	{
		xpm->addr[i] = malloc(CBSZ * sizeof(int));
		i++;
	}
	xpm->img = mlx_xpm_file_to_image(settings->win->mlx, settings->path_no, &xpm->width, &xpm->height); // TODO: проверка на нул
	if (xpm->img == NULL)
		error(23);
//	if (xpm->width != 64 || xpm->height != 64)
//		error(23);
	addr = (int*)mlx_get_data_addr(xpm->img, &xpm->bpp, &xpm->line_l, &xpm->en);
	i = 0;
	ii = 0;
	while (i < (CBSZ - 1) * (CBSZ -1))
	{
		iii = 0;
		while (iii < CBSZ)
		{
			xpm->addr[ii][iii] = addr[i];
			iii++;
			i++;
		}
		ii++;
	}
	return(0);
}*/
void		make_xpm_revers(t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;
	
	xpm->addr[side] = (int**)malloc(xpm->height * sizeof(int *));
	i = 0;
	while (i < xpm->height)
	{
		xpm->addr[side][i] = malloc(xpm->width * sizeof(int));
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height -1))
	{
		iii = xpm->width - 1;
		while (iii >= 0)
		{
			xpm->addr[side][ii][iii] = array[i];
			iii--;
			i++;
		}
		ii++;
	}
}

void		make_xpm(t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;
	
	xpm->addr[side] = (int**)malloc(xpm->height * sizeof(int *));
	i = 0;
	while (i < xpm->height)
	{
		xpm->addr[side][i] = malloc(xpm->width * sizeof(int));
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height -1))
	{
		iii = 0;
		while (iii < xpm->width)
		{
			xpm->addr[side][ii][iii] = array[i];
			iii++;
			i++;
		}
		ii++;
	}
}
void		load_textures(t_settings *settings, t_xpm *xpm, char **line, int side)
{
//	t_xpm xpm;
//	settings->xpm = &xpm;
	int *array;

	if (xpm->addr == NULL)
		xpm->addr = (int***)malloc(5 * sizeof(int **));
	xpm->img = mlx_xpm_file_to_image(settings->win->mlx, line[1], &xpm->width, &xpm->height); // TODO: проверка на нул
	if (xpm->img == NULL)
		error(23);
	array = (int*)mlx_get_data_addr(xpm->img, &xpm->bpp, &xpm->line_l, &xpm->en);
	if (array == NULL)
		error(23);
	if (side == 1 || side == 0)
		make_xpm(xpm, array, side);
	else
		make_xpm_revers(xpm, array, side);
	
//	else
//		make_xpm_revers();
}

/* void	path_pars(char **line, char **way)
{
		int fd;
//		printf("way = %s", *way);
		if (*way != NULL)
			error(19);
		if (line[1] == NULL || line[2] != NULL || (fd = open(line[1], O_APPEND)) == -1)
			error(18);
		*way = line[1];
		line[1] = ft_strdup("");
		free_char_arr((void**)line); */