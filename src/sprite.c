#include "../includes/cub3D.h"

void	new_sprite(int y, int x, t_settings *set)
{
	t_sprite	*tmp;
	t_sprite	*new;

	tmp = set->sprite;
	if (tmp == NULL)
	{
		tmp = (t_sprite *)malloc(sizeof(t_sprite));
		tmp->x = x * CBSZ + CBSZ / 2;
		tmp->y = y * CBSZ + CBSZ / 2;
		tmp->next = NULL;
		set->sprite = tmp;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (!(new = (t_sprite *)malloc(sizeof(t_sprite))))
			error("Malloc problem(fn_new_sprite)", set);
		new->x = x * CBSZ + CBSZ / 2;
		new->y = y * CBSZ + CBSZ / 2;
		new->next = NULL;
		tmp->next = new;
	}
}

void	drow_sprite(t_settings *set, t_sprite *sprite)
{
	int		start_x;
	int		start_y;
	int		i;
	int		ii;
	float	size;
	int		color;
	float	xpm_scale;
	float	scale_x;
	float	scale_y;

	i = 0;
	ii = 0;
	size = CBSZ / sprite->dist * 2000;
	scale_x = size / set->xpm[4].width;
	scale_y = size / set->xpm[4].height;
	start_x = set->resol_x / 2 - (set->resol_x / (M_PI / 3)) * sprite->angle - size / 2;
	start_y = set->resol_y / 2 - size / 2;
	while (ii < size && (ii + start_x) < set->resol_x)
	{
		if (set->ray->all_dist[start_x + ii] > sprite->dist)
		{
			i = 0;
			while (i < size && (i + start_y) < set->resol_y)
			{
				color = set->xpm[4].addr[(int)(i / scale_y)][(int)(ii / scale_x)];
				if (color != 0)
					my_mlx_pixel_put(set, start_x + ii, start_y + i, color);
				i++;
			}
		}
		ii++;
	}
}

void	sprite_sort(t_settings *set)
{
	t_sprite	*tmp;
	t_sprite	*sprite_max;
	float		dist_max;

	tmp = set->sprite;
	while (tmp != NULL)
	{
		tmp->angle = atan2(set->plr->y - tmp->y, tmp->x - set->plr->x);
		if (tmp->angle < 0 && set->plr->pov >= M_PI / 6 && set->plr->pov <= (M_PI * 2 - M_PI / 6))
			tmp->angle += 2 * M_PI;
		if (set->plr->pov > (M_PI * 2 - M_PI / 6) && set->plr->pov <= 7)
			tmp->angle += 2 * M_PI;
		tmp->angle -= set->plr->pov;
		if (tmp->angle > -M_PI / 6 && tmp->angle < M_PI / 6)
			tmp->dist = sqrt(pow(set->plr->x - tmp->x, 2) + pow(set->plr->y - tmp->y, 2));
		else
			tmp->dist = -1;
		tmp = tmp->next;
	}
	dist_max = 0;
	while (dist_max != -1)
	{
		tmp = set->sprite;
		dist_max = -1;
		while (tmp != NULL)
		{
			if (tmp->dist > dist_max)
			{
				dist_max = tmp->dist;
				sprite_max = tmp;
			}
			tmp = tmp->next;
		}
		if (dist_max != -1)
		{
			drow_sprite(set, sprite_max);
			sprite_max->dist = -1;
		}
	}
}
