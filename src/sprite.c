/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:37:28 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:37:30 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	new->wid_scale = set->x / (float)1920 * set->xpm[4].width;
	new->hei_scale = set->y / (float)1080 * set->xpm[4].height;
	if (new->wid_scale > set->x || new->hei_scale > set->y)
	{
		new->wid_scale = new->wid_scale * 500 / new->wid_scale;
		new->hei_scale = new->wid_scale * 500 / new->wid_scale;
	}
}

int		get_color(t_settings *set, float h, float w)
{
	return (set->xpm[4].addr[(int)((float)set->xpm[4].height * h)]
	[(int)((float)set->xpm[4].width * w)]);
}

void	drow_sprite(t_settings *set, t_sprite *sprite, int i, int ii)
{
	int		x;
	int		y;
	float	w;
	float	h;

	w = (float)CBSZ / sprite->dist * sprite->wid_scale;
	h = (float)CBSZ / sprite->dist * sprite->hei_scale;
	x = set->x / 2 - (set->x / (M_PI / 3)) * sprite->angle - w / 2;
	y = set->y / 2 - h / 2;
	while (ii < w && (ii + x) < set->x)
	{
		if ((x + ii) >= 0 && (x + ii) < set->x &&
			set->ray->all_dist[x + ii] > sprite->dist)
		{
			i = 0;
			while (i < h)
			{
				if ((sprite->color = get_color(set, (float)(i / h),
					(float)(ii / w))))
					pixel_put(set, x + ii, y + i, sprite->color);
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
		if (tmp->angle > -M_PI / 4 && tmp->angle < M_PI / 4)
			tmp->dist = sqrt(pow(set->plr->x - tmp->x, 2) +
			pow(set->plr->y - tmp->y, 2));
		else
			tmp->dist = -1;
		if (tmp->dist > 0 && tmp->dist < CBSZ / 7)
			tmp->dist = -1;
		tmp = tmp->next;
	}
	sprite_sort(set);
}
