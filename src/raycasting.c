#include "../includes/cub3D.h"
#include <math.h>

int		remains_by_bits(int value, int base)
{
	return (value & (base - 1));
}

float	cross_finder(t_settings *set, float *x, float *y)
{
	float	status;
	float	x_n;
	float	y_n;

	status = 0;
	while (status == 0)
	{
		x_n = (int)*x / CBSZ;
		y_n = (int)*y / CBSZ;
		if (x_n > set->max_x || y_n > set->max_y || x_n < 0 || y_n < 0)
			status = INT_MAX;
		else if (set->map[(int)y_n][(int)x_n] == ' ')
			status = INT_MAX;
		else if (set->map[(int)y_n][(int)x_n] == '1')
			status = sqrt(pow(set->plr->x - *x, 2) + pow(set->plr->y - *y, 2));
		else
		{
			*x += set->ray->x_step;
			*y += set->ray->y_step;
		}
	}
	return (status);
}

void	cross_vert(t_settings *set, float x, float y, int side)
{
	float	dist;

	set->ray->x_step = CBSZ;
	set->ray->y_step = CBSZ * set->ray->tg;
	if (set->ray->angle > M_PI_2 && set->ray->angle < M_PI * 3 / 2)
	{
		x = set->ray->x_midl - 0.001;
		set->ray->x_step = -set->ray->x_step;
	}
	else
	{
		side = 0;
		x = set->ray->x_midl + CBSZ;
		set->ray->y_step = -set->ray->y_step;
	}
	y = set->plr->y + (set->plr->x - x) * set->ray->tg;
	dist = cross_finder(set, &x, &y);
	if (set->ray->dist > dist)
	{
		set->ray->side = side;
		set->ray->dist = dist;
		set->ray->plase = y;
	}
	set->ray->plase = remains_by_bits(set->ray->plase, CBSZ);
}

void	cross_horiz(t_settings *set, float x, float y)
{
	float angle;

	angle = set->ray->angle;
	set->ray->y_step = CBSZ;
	set->ray->x_step = CBSZ / set->ray->tg;
	if ((angle > 0 && angle < M_PI) || angle > M_PI * 2)
	{
		set->ray->side = 1;
		y = set->ray->y_midl - 0.001;
		set->ray->y_step = -set->ray->y_step;
	}
	else
	{
		set->ray->side = 3;
		y = set->ray->y_midl + CBSZ;
		set->ray->x_step = -set->ray->x_step;
	}
	x = set->plr->x + (set->plr->y - y) / set->ray->tg;
	set->ray->dist = cross_finder(set, &x, &y);
	set->ray->plase = x;
}

void	ray_emission(t_settings *set, float view_start, int i)
{
	set->ray->angle = view_start;
	set->ray->x_midl = (int)(set->plr->x / CBSZ) * CBSZ;
	set->ray->y_midl = (int)(set->plr->y / CBSZ) * CBSZ;
	while (i <= set->resol_x)
	{
		set->ray->tg = tan(set->ray->angle);
		cross_horiz(set, 0, 0);
		cross_vert(set, 0, 0, 2);
		set->ray->all_dist[i] = set->ray->dist;
		set->ray->dist *= cos(set->ray->angle - set->plr->pov);
		column_draw(set, set->ray->dist, set->ray->side, (int)set->ray->plase);
		set->ray->angle -= set->ray->step;
		i++;
	}
}
