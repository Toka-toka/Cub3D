/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:34:50 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:34:53 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	my_mlx_pixel_put(t_settings *settings, int x, int y, int color)
{
	char*pixel;

	if (x >= 0 && y >= 0)
	{
		pixel = settings->win->addr +
		(y * settings->win->line_l + x * (settings->win->bpp / 8));
		*(unsigned int*)pixel = color;
	}
}

void	column_scale(t_settings *settings, t_ray *ray)
{
	ray->column_h = CBSZ / ray->dist * settings->win->constant * 3;
	ray->xpm_scale = ray->column_h / settings->xpm[ray->side].height;
	if ((int)ray->column_h >= settings->resol_y)
	{
		ray->floor_h = 0;
		ray->ceiling_h = 0;
		ray->column_y = (ray->column_h - settings->resol_y) / 2;
		ray->column_h = ray->column_y + settings->resol_y;
	}
	else
	{
		ray->floor_h = (settings->resol_y - ray->column_h) / 2;
		ray->ceiling_h = ray->floor_h;
		ray->column_y = 0;
	}
}

void	column_draw(t_settings *settings, t_ray *ray, int x, int y)
{
	column_scale(settings, ray);
	while (ray->floor_h > 0)
	{
		my_mlx_pixel_put(settings, x, y, settings->color_f[0]);
		ray->floor_h--;
		y++;
	}
	ray->plase = ray->plase * settings->xpm[ray->side].wid_scale;
	while (ray->column_y < ray->column_h)
	{
		my_mlx_pixel_put(settings, x, y, settings->xpm[ray->side].addr
		[(int)(ray->column_y / ray->xpm_scale)][ray->plase]);
		ray->column_y++;
		y++;
	}
	while (ray->ceiling_h > 0)
	{
		my_mlx_pixel_put(settings, x, y, settings->color_c[0]);
		y++;
		ray->ceiling_h--;
	}
}
