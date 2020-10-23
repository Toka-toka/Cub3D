/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:38:15 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:38:18 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void		make_xpm_revers(t_settings *set, t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;

	xpm->addr = (int**)malloc((xpm->height + 1) * sizeof(int *));
	if (xpm->addr == NULL)
		error("Malloc problem (fn_make_xpm)", set);
	i = 0;
	while (i < xpm->height)
	{
		if (!(xpm->addr[i] = malloc(xpm->width * sizeof(int))))
			error("Malloc problem (fn_make_xpm)", set);
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height - 1))
	{
		iii = xpm->width - 1;
		while (iii >= 0)
			xpm->addr[ii][iii--] = array[i++];
		ii++;
	}
	xpm->addr[xpm->height] = NULL;
}

void		make_xpm(t_settings *set, t_xpm *xpm, int *array, int side)
{
	int i;
	int ii;
	int iii;

	xpm->addr = (int**)malloc((xpm->height + 1) * sizeof(int *));
	if (xpm->addr == NULL)
		error("Malloc problem (fn_make_xpm)", set);
	i = 0;
	while (i < xpm->height)
	{
		if (!(xpm->addr[i] = malloc(xpm->width * sizeof(int))))
			error("Malloc problem (fn_make_xpm)", set);
		i++;
	}
	i = 0;
	ii = 0;
	while (i < (xpm->width - 1) * (xpm->height - 1))
	{
		iii = 0;
		while (iii < xpm->width)
			xpm->addr[ii][iii++] = array[i++];
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
		make_xpm(set, x, array, side);
	else
		make_xpm_revers(set, x, array, side);
	mlx_destroy_image(set->win->mlx, x->img);
}
