# include "../includes/cub3D.h"

void	new_sprite(int y, int x, t_settings *settings)
{
//	t_sprite	*new;
	t_sprite	*current;
	t_sprite	*new;

	current = settings->sprite;
	if (current == NULL)
	{
		current = (t_sprite *)malloc(sizeof(t_sprite));
		current->x = x * CBSZ + CBSZ / 2;
		current->y = y * CBSZ + CBSZ / 2;
		current->next = NULL;
		settings->sprite = current;
	}
	else
	{
		while (current->next != NULL)
			current = current->next;
		if (!(new = (t_sprite *)malloc(sizeof(t_sprite))))
			error (4);
		new->x = x * CBSZ + CBSZ / 2;
		new->y = y * CBSZ + CBSZ / 2;
		new->next = NULL;
//	new->angle = atan2(new->x - settings->location_x, new->y - settings->location_y);
		current->next = new;
	}
}

void	drow_sprite(t_settings *settings, t_sprite *sprite)
{
	int start_x;
	int start_y;
	int i;
	int ii;
	int scale;
	float check;

	i = 0;
	ii = 0;
	scale = 300 * (float)(1000 / sprite->dist);
	start_x = settings->resol_x / 2 - (settings->resol_x / (M_PI / 3)) * sprite->angle;
	start_y = settings->resol_y / 2;
	while (i < scale && (i + start_y) < settings->resol_y)
	{
		ii = 0;
		while (ii < scale && (ii + start_x) < settings->resol_x)
		{
			if (settings->rays[start_x + ii] > sprite->dist)
			{
				check = settings->rays[start_x + ii];
				my_mlx_pixel_put(settings, start_x + ii, start_y + i, sprite->color);
			}
			ii++;
		}
		i++;
	}
}

void	sprite_sort(t_settings *settings)
{
	t_sprite	*current;
	t_sprite	*sprite_max;
	float		dist_max;

	current = settings->sprite;
	current->color = 0xff00;
	current = current->next;
	current->color = 0xffa500;
	current = current->next;
	current->color = 0xff; //
	current = current->next;
	current->color = 0xff0000; //
	current = current->next;	
	current->color = 0;
	current = current->next;
	current = settings->sprite;
	while (current != NULL)
	{
		current->angle = atan2(settings->location_y - current->y, current->x - settings->location_x);
		if (current->angle < 0 && settings->orientation > M_PI / 3)
			current->angle += 2 * M_PI;
		current->angle -= settings->orientation;
		if (current->angle > - (M_PI / 6) && current->angle < M_PI / 6)
		{
//			if (current->angle < 0)
//				current->angle -= current->angle;
			current->dist = sqrt (pow(settings->location_x - current->x, 2) + pow(settings->location_y - current->y, 2));
//			current->angle += M_PI / 6;
		}
		else 
			current->dist = -1;
		current = current->next;
	}
	dist_max = 0;
	while (dist_max != -1)
	{
		current = settings->sprite;
		dist_max = -1;
		while (current != NULL)
		{
			if (current->dist > dist_max)
			{
				dist_max = current->dist;
				sprite_max = current;
			}
			current = current->next;
		}
		if (dist_max != -1)
			drow_sprite(settings, sprite_max);
//		printf("dist_max = %f", dist_max);
		sprite_max->dist = -1;
	}
}