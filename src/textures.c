#include "../includes/cub3D.h"

void		make_xpm_revers(t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;

	xpm->addr = (int**)malloc((xpm->height + 1) * sizeof(int *)); //TODO: не защищены маллоки
	i = 0;
	while (i < xpm->height)
	{
		xpm->addr[i] = malloc(xpm->width * sizeof(int));
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height - 1))
	{
		iii = xpm->width - 1;
		while (iii >= 0)
		{
			xpm->addr[ii][iii] = array[i];
			iii--;
			i++;
		}
		ii++;
	}
	xpm->addr[xpm->height] = NULL;
}

void		make_xpm(t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;

	xpm->addr = (int**)malloc((xpm->height + 1) * sizeof(int *));
	i = 0;
	while (i < xpm->height)
	{
		xpm->addr[i] = malloc(xpm->width * sizeof(int));
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height - 1))
	{
		iii = 0;
		while (iii < xpm->width)
		{
			xpm->addr[ii][iii] = array[i];
			iii++;
			i++;
		}
		ii++;
	}
	xpm->addr[xpm->height] = NULL;
}

void		load_textures(t_settings *set, t_xpm *x, char *l, int side)
{
	int *array;
	int	line_l;
	int	bpp;
	int	en;

	while (*l == ' ')
		l++;
	x->img = mlx_xpm_file_to_image(set->win->mlx, l, &x->width, &x->height);
	if (x->img == NULL)
	{
		set->xpm[side].addr = NULL;
		error("Problem with textures", set);
	}
	array = (int*)mlx_get_data_addr(x->img, &bpp, &line_l, &en);
	x->wid_scale = (float)x->width / (float)CBSZ;
	if (array == NULL)
	{
		set->xpm[side].addr = NULL;
		error("Problem with textures", set);
	}
	if (side == 1 || side == 0 || side == 4)
		make_xpm(x, array, side);
	else
		make_xpm_revers(x, array, side);
	mlx_destroy_image (set->win->mlx, x->img);
}
