# include "../includes/cub3D.h"

void	txt_drow(t_settings *settings, int i, int ii, int color)
{
	i = i * 4;
	ii = ii * 4;
	
	my_mlx_pixel_put(settings, i, ii, color);
	my_mlx_pixel_put(settings, i + 1, ii, color);
	my_mlx_pixel_put(settings, i + 2, ii, color);
	my_mlx_pixel_put(settings, i + 3, ii, color);
	my_mlx_pixel_put(settings, i, ii + 1, color);
	my_mlx_pixel_put(settings, i + 1, ii + 1, color);
	my_mlx_pixel_put(settings, i + 2, ii + 1, color);
	my_mlx_pixel_put(settings, i + 3, ii + 1, color);	
	my_mlx_pixel_put(settings, i, ii + 2, color);
	my_mlx_pixel_put(settings, i + 1, ii + 2, color);
	my_mlx_pixel_put(settings, i + 2, ii + 2, color);
	my_mlx_pixel_put(settings, i + 3, ii + 2, color);	
	my_mlx_pixel_put(settings, i, ii + 3, color);
	my_mlx_pixel_put(settings, i + 1, ii + 3, color);
	my_mlx_pixel_put(settings, i + 2, ii + 3, color);
	my_mlx_pixel_put(settings, i + 3, ii + 3, color);
}

int			open_xpm(t_settings *settings, t_xpm *xpm)
{
	int xpm_data[64][64];

	int i;
	int ii;
	int iii;

	// TODO: попробовать открыть файл
	xpm->img = mlx_xpm_file_to_image(settings->win->mlx, settings->path_no, &xpm->width, &xpm->height); // TODO: проверка на нул
	if (xpm->img == NULL)
		error(23);
	if (xpm->width != 64 || xpm->height != 64)
		error(23);
	xpm->addr = (int*)mlx_get_data_addr(xpm->img, &xpm->bpp, &xpm->line_l, &xpm->en);
	i = 0;
	ii = 0;
	while (i < 63 * 63)
	{
		iii = 0;
		while (iii < 64)
		{
			xpm_data[ii][iii] = xpm->addr[i];
//			txt_drow(settings, iii, ii, xpm_data[ii][iii]);
			iii++;
			i++;
		}
		ii++;
	}
	return(0);
}

void		load_textures(t_settings *settings)
{
	t_xpm xpm;
	settings->xpm = &xpm;
	open_xpm(settings, settings->xpm);
}