# include "../includes/cub3D.h"
# include <math.h>

int		cross_finder(t_settings *settings, float x, float y)
{
	x = (int)x / CBSZ;
	y = (int)y / CBSZ;
	if (x > settings->max_x || y > settings->max_y || x < 0 || y < 0 || settings->map[(int)y][(int)x] == ' ')
		return(-1);
	else if (settings->map[(int)y][(int)x] == '1')
		return(1);
	else
		return(0);
}

float	cross_vert(t_settings *settings, float ray_angle, int*	vert, int* side)
{
	float x;
	float y;
	float step_x;
	float step_y;
	int cross_status;

	step_x = CBSZ;
	step_y = CBSZ * tan(ray_angle);
	if (ray_angle > M_PI_2 && ray_angle <  M_PI * 3 / 2)
	{
		*side = 2;
		x = (int)(settings->location_x / CBSZ) * CBSZ - 0.001;
		step_x = -step_x;
	}
	else
	{
		*side = 0;
		x = (int)(settings->location_x / CBSZ) * CBSZ + CBSZ;
		step_y = - step_y;
	}
	y = settings->location_y + (settings->location_x - x) * tan(ray_angle);
	while ((cross_status = cross_finder(settings, x, y)) == 0)
	{
		x += step_x;
		y += step_y;
	}
	if (cross_status == -1)
		return(10000000);
	*vert = (int)y;
	return(sqrt (pow(settings->location_x - x, 2) + pow(settings->location_y - y, 2)));
}

float	cross_horiz(t_settings *settings, float ray_angle, int* horiz, int* side)
{
	float x;
	float y;
	float step_x;
	float step_y;
	int cross_status;

	step_y = CBSZ;
	step_x = CBSZ / tan(ray_angle);
	if ((ray_angle > 0 && ray_angle <  M_PI) || ray_angle > M_PI * 2)
	{
		*side = 1;
		y = (int)(settings->location_y / CBSZ) * CBSZ - 0.001;
		step_y = -step_y;
	}
	else
	{
		*side = 3;
		y = (int)(settings->location_y / CBSZ) * CBSZ + CBSZ;
		step_x = - step_x;
	}
	x = settings->location_x + (settings->location_y - y) / tan(ray_angle);
	while ((cross_status = cross_finder(settings, x, y)) == 0)
	{
		x += step_x;
		y += step_y;
	}
	if (cross_status == -1)
		return(10000000);
	*horiz = (int)x;
	return(sqrt (pow(settings->location_x - x, 2) + pow(settings->location_y - y, 2)));
}

void	ray_emission(t_settings *settings)
{
	float view_start;
	float view_step;
	float dist_horiz;
	float dist_vert;

	int 	vert;
	int 	horiz;
	
	int side_vert;
	int side_horiz;

	int i;

	view_start = settings->orientation + M_PI / 6;
	view_step = M_PI / 3 / settings->resol_x;
	i = 0;
	while (i <= settings->resol_x)
	{
		dist_horiz = cross_horiz(settings, view_start, &horiz, &side_horiz);
		dist_vert = cross_vert(settings, view_start, &vert, &side_vert);
		if (dist_horiz < dist_vert)
		{
			column_draw(dist_horiz * cos(view_start - settings->orientation), settings, horiz, side_horiz);
			settings->rays[i] = dist_horiz * cos(view_start - settings->orientation);
		}
		else
		{
			column_draw(dist_vert * cos(view_start - settings->orientation), settings, vert, side_vert);
			settings->rays[i] = dist_vert * cos(view_start - settings->orientation);
		}
		view_start -= view_step;
		i++;
	}
/*	view_start = settings->orientation + M_PI / 6; // эта строчка и до 133 нужны, чтобы отрисовать лучи на миникарте 
	map_hero_draw(settings);
	while (view_start > view_end)
	{
		y = settings->location_y;
		x = settings->location_x;
		while (settings->map[(int)y / CBSZ][(int)x / CBSZ] == '0')
		{
			y -= sin(view_start);
			x += cos(view_start);
			my_mlx_pixel_put(settings, x, y, 0x20b2aa);
		}
		view_start -= view_step; 
	} */
}