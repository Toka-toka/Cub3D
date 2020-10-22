#include "../includes/cub3D.h"

void	new_sprite(int y, int x, t_settings *set)
{
	t_sprite	*tmp;
	t_sprite	*new;

	if (!(new = (t_sprite *)malloc(sizeof(t_sprite))))
		error("Malloc problem(fn_new_sprite)", set);
	if (set->sprite == NULL)
		set->sprite = new;
	else
	{
		tmp = set->sprite;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->x = x * CBSZ + CBSZ / 2;
	new->y = y * CBSZ + CBSZ / 2;
	new->next = NULL;
	new->wid_scale = set->resol_x / (float)1920 * set->xpm[4].width;
	new->hei_scale = set->resol_y / (float)1080 * set->xpm[4].height;
}

void	drow_sprite(t_settings *set, t_sprite *sprite, int i, int ii)
{
	int		start_x;
	int		start_y;
	float	scale_x;
	float	scale_y;

	scale_x = CBSZ / sprite->dist * sprite->wid_scale;
	scale_y = CBSZ / sprite->dist * sprite->hei_scale;
	start_x = set->resol_x / 2 - (set->resol_x / (M_PI / 3)) * sprite->angle - scale_x / 2;
	start_y = set->resol_y / 2 - scale_y / 2;
	while (ii < scale_x && (ii + start_x) < set->resol_x)
	{
		if (set->ray->all_dist[start_x + ii] > sprite->dist)
		{
			i = 0;
			while (i < scale_y && (i + start_y) < set->resol_y)
			{
				sprite->color = set->xpm[4].addr[(int)(i * (float)set->xpm[4].height / scale_y)]
				[(int)(ii * (float)set->xpm[4].width / scale_x)];
				if (sprite->color != 0)
					my_mlx_pixel_put(set, start_x + ii, start_y + i, sprite->color);
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
			drow_sprite(set, sprite_max, 0, 0);
			sprite_max->dist = -1;
		}
	}
}

void	sprite_finder(t_settings *set)
{
	t_sprite	*tmp;

	tmp = set->sprite;
	while (tmp != NULL)
	{
		tmp->angle = atan2(set->plr->y - tmp->y, tmp->x - set->plr->x);
		if (tmp->angle < 0 && set->plr->pov >= M_PI / 6 &&
			set->plr->pov <= (M_PI * 2 - M_PI / 6))
			tmp->angle += 2 * M_PI;
		if (set->plr->pov > (M_PI * 2 - M_PI / 6) && set->plr->pov <= 7)
			tmp->angle += 2 * M_PI;
		tmp->angle -= set->plr->pov;
		if (tmp->angle > -M_PI / 6 && tmp->angle < M_PI / 6)
			tmp->dist = sqrt(pow(set->plr->x - tmp->x, 2) +
			pow(set->plr->y - tmp->y, 2));
		else
			tmp->dist = -1;
		if (tmp->dist < CBSZ / 5)
			tmp->dist = -1;
		tmp = tmp->next;
	}
	sprite_sort(set);
}
