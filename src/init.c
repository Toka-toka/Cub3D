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

	float view_start = settings->orientation - M_PI_4;
	float view_end = settings->orientation + M_PI_4;

	conts = settings->resol_x / 2 * tan(M_PI_4);
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
		while (settings->map[(int)y / CBSZ][(int)x / CBSZ] != '1')
		{
			if (settings->map[(int)y / CBSZ][(int)x / CBSZ] == '0')
				step = 16;
			else if (settings->map[(int)y / CBSZ][(int)x / CBSZ] == '5')
				step = 1;
			y += sin(view_start) * step;
			x += cos(view_start) * step;
			my_mlx_pixel_put(settings, x, y, 0x20b2aa);
		}
		column_d = sqrt (pow(settings->location_x - x, 2) + pow(settings->location_y - y, 2)); // * cos(view_start);
		column_h = 64 / column_d * conts;
		game_draw(settings, column_h, i);
		view_start += M_PI_2 / 1920;
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
	
	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
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
			pixel_map(settings, x, y, color);
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

int	close_window(int keycode, t_settings *settings)
{
	if (keycode == 65307) // esc
	{
		mlx_destroy_window(settings->win_3d->mlx_ptr, settings->win_3d->window_ptr);
		mlx_destroy_window(settings->mlx_ptr, settings->window_ptr);
		exit(1);
	}
	if (keycode == 119) // && settings->map[(int)(settings->location_y + 16) / CBSZ][(int)(settings->location_x + 16) / CBSZ] != '1') // w
	{
		settings->location_y += sin(settings->orientation) * CBSZ;
		settings->location_x += cos(settings->orientation) * CBSZ;
	} 
//	if (keycode == 119) // w
//	{
//		make_img(settings);
//	} 
	if (keycode == 115) // && settings->map[(int)(settings->location_y - 16) / CBSZ][(int)(settings->location_x - 16) / CBSZ] != '1') // s 
	{
		settings->location_y -= sin(settings->orientation) * CBSZ / 4;
		settings->location_x -= cos(settings->orientation) * CBSZ / 4;
	}
	if (keycode == 97)
	{
		settings->orientation -= M_PI / 16;
	}
	if (keycode == 100)
	{
		settings->orientation += M_PI / 16;
	}
//	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
	map_hero_draw(settings);
	return(0);
}

void	init_window(t_settings *settings)
{
	settings->mlx_ptr = mlx_init();
	settings->window_ptr = mlx_new_window(settings->mlx_ptr, 1100, 480, "map");
	settings->win->img = mlx_new_image(settings->mlx_ptr, 1100, 480);
	settings->win->addr = mlx_get_data_addr(settings->win->img, &settings->win->bpp, &settings->win->line_l, &settings->win->en);

	settings->win_3d->mlx_ptr = mlx_init();
	settings->win_3d->window_ptr = mlx_new_window(settings->mlx_ptr, settings->resol_x, settings->resol_y, "game");
	settings->win_3d->img = mlx_new_image(settings->mlx_ptr, settings->resol_x, settings->resol_y);
	settings->win_3d->addr = mlx_get_data_addr(settings->win_3d->img, &settings->win_3d->bpp, &settings->win_3d->line_l, &settings->win_3d->en);
	
	map_hero_draw(settings);
	mlx_key_hook(settings->window_ptr, close_window, settings);
	mlx_loop(settings->mlx_ptr);
	mlx_loop(settings->win_3d->mlx_ptr);
	exit(1);
//	return (0);
}