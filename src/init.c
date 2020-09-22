# include "../includes/cub3D.h"

void	my_mlx_pixel_put_game(t_settings *settings, int x, int y, int color)
{
    char    *pixel;

    pixel = settings->win_3d->addr + (y * settings->win_3d->line_l + x * (settings->win_3d->bpp / 8));
    *(unsigned int*)pixel = color;
}

void	my_mlx_pixel_put(t_settings *settings, int x, int y, int color)
{
    char    *pixel;

    pixel = settings->win->addr + (y * settings->win->line_l + x * (settings->win->bpp / 8));
    *(unsigned int*)pixel = color;
}

void	pixel_map(t_settings *settings, int x, int y, int color)
{
	int i = 0;
	int ii = 0;
	int x_start = 0;

	x_start = x;
	while (i < CBSZ)
	{
		x = x_start;
		ii = 0;
		while (ii < CBSZ)
		{		
			if (ii == 0 || i == 0)
				my_mlx_pixel_put(settings, x, y, 0xbfbfbf);
			else my_mlx_pixel_put(settings, x, y, color);
			x++;
			ii++;
		}
		i++;
		y++;
	}
}

void	game_draw(t_settings *settings, float column_h, int x)
{
		int y = 0;
		int y_start_col;

		y_start_col = settings->resol_y / 2 - column_h / 2;
		while (y < settings->resol_y)
		{
			while (y < y_start_col && y < settings->resol_y)
			{
				my_mlx_pixel_put_game(settings, x, y, 0x87ceeb); //blue
				y++;
			}
			while (column_h > 0 && y < settings->resol_y)
			{
				my_mlx_pixel_put_game(settings, x, y, 0xff6347); //red
				column_h--;
				y++;
			}
		my_mlx_pixel_put_game(settings, x, y, 0x708090); //green
		y++;
		}
}

void	pixel_hero(t_settings *settings, int color)
{
	float y = 0;
	float x = 0;
	float conts = 0;
	float column_d = 0;
	float column_h = 0;
	int	i = 0;
	int step = 1;
	float step_y = 0;
	float step_x = 0;

	float view_start = settings->orientation - M_PI / 6;
	float view_end = settings->orientation + M_PI / 6;

	conts = (float)settings->resol_x / 2 * tan(M_PI / 3);
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{		
			my_mlx_pixel_put(settings, settings->location_x + x - 4, settings->location_y + y - 4, 0xff0000);
			x++;
		}
		y++;
	}
	y = settings->location_y;
	x = settings->location_x;
	while (view_start < view_end)
	{
		y = settings->location_y;
		step_y = sin(view_start) / step;
		step_x = cos(view_start) / step;
		while (settings->map[(int)y / CBSZ][(int)x / CBSZ] != '1') // TODO: вернуть "быстрые" шаги луча
		{
///			if (settings->map[(int)y / CBSZ][(int)x / CBSZ] == '0')
//			{
//				step = 16;
//				y += sin(view_start) * step;
//				x += cos(view_start) * step;
//			}
//			else if (settings->map[(int)y / CBSZ][(int)x / CBSZ] == '5')
//			{
				step = 5;
				y += step_y;
				x += step_x;
//			}
			my_mlx_pixel_put(settings, x, y, 0x20b2aa);
		}
		column_d = sqrt (pow(settings->location_x - x, 2) + pow(settings->location_y - y, 2)); // * cos(view_start);
		column_d = column_d * cos(view_start - settings->orientation);
		column_h = 64 / column_d * conts;
//		printf("view_start = %f, x = %f, y = %f, column_d = %f, column_h = %f column_h = %d\n", view_start, x, y, column_d, column_h, (int)column_h);
		game_draw(settings, column_h, i);
		view_start += M_PI / 3 / 1920;
		i++;
		x = settings->location_x;
	}
}

void	map_hero_draw(t_settings *settings)
{
	int i = 0;
	int ii = 0;
	int x = 0;
	int y = 0;
	int color;
	
//	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
	x = 0;
	i = 0;
	while (settings->map[i] != NULL)
	{
		ii = 0;
		x = 0;
		while (settings->map[i][ii] != '\0')
		{
			if (settings->map[i][ii] == '1')
				color = 0x708090; //blue
			else if (settings->map[i][ii] == ' ')
				color = 0x0; // black
			else if (settings->map[i][ii] == '2')
				color = 0xff00; //green
			else if (settings->map[i][ii] == '0')
				color = 0xffffff;
			else if (settings->map[i][ii] == '5')
				color = 0xf0f0f0;
//			pixel_map(settings, x, y, color);
			x += CBSZ;
			ii++;
		}
		i++;
		y += CBSZ;
	}
	pixel_hero (settings, color);
	mlx_put_image_to_window(settings->mlx_ptr, settings->window_ptr, settings->win->img, 0, 0);
	mlx_put_image_to_window(settings->win_3d->mlx_ptr, settings->win_3d->window_ptr, settings->win_3d->img, 0, 0);
}

//int	close_window(int keycode, t_settings *settings)
//{
//
//	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
//	map_hero_draw(settings);
//	return(0);
//}

void	init_window(t_settings *settings)
{
	settings->mlx_ptr = mlx_init();
	settings->window_ptr = mlx_new_window(settings->mlx_ptr, 1100, 480, "map");
	settings->win->img = mlx_new_image(settings->mlx_ptr, 1100, 480);
	settings->win->addr = mlx_get_data_addr(settings->win->img, &settings->win->bpp, &settings->win->line_l, &settings->win->en);

	settings->win_3d->mlx_ptr = mlx_init();
	settings->win_3d->window_ptr = mlx_new_window(settings->win_3d->mlx_ptr, settings->resol_x, settings->resol_y, "game");
	settings->win_3d->img = mlx_new_image(settings->win_3d->mlx_ptr, settings->resol_x, settings->resol_y);
	settings->win_3d->addr = mlx_get_data_addr(settings->win_3d->img, &settings->win_3d->bpp, &settings->win_3d->line_l, &settings->win_3d->en);
	
	map_hero_draw(settings);

	mlx_hook(settings->win_3d->window_ptr, 2, 1L << 0, key_pressed, settings);
	mlx_hook(settings->win_3d->window_ptr, 3, 1L << 1, key_released, settings);
	mlx_loop_hook(settings->win_3d->mlx_ptr, actions_call, settings);
	mlx_loop(settings->win_3d->mlx_ptr);
	exit(1);
}