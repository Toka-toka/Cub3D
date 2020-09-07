# include "../includes/cub3D.h"

void	pixel_map(t_settings *settings, int x, int y, int color)
{
	int i = 0;
	int ii = 0;
	int x_start = 0;

	x_start = x;
	while (i < 20)
	{
		x = x_start;
		ii = 0;
		while (ii < 20)
		{		
			mlx_pixel_put(settings->mlx_ptr, settings->window_ptr, x, y, color);
			x++;
			ii++;
		}
		i++;
		y++;
	}
}

void	pixel_hero(t_settings *settings, int color)
{
	float i = 0;
	float ii = 0;

	float view_start = settings->orientation - M_PI_4;
	float view_end = settings->orientation + M_PI_4;

	while (i < 10)
	{
		ii = 0;
		while (ii < 10)
		{		
			mlx_pixel_put(settings->mlx_ptr, settings->window_ptr, settings->location_x + ii - 5, settings->location_y + i - 5, color);
			ii++;
		}
		i++;
	}
	i = settings->location_y;
	ii = settings->location_x;
	printf("\nlocation_x = %d\nsettings->location_y = %d\nsettings->orientation = %f",  settings->location_x,  settings->location_y, settings->orientation / M_PI);
	while (view_start < view_end)
	{
		i = settings->location_y;
		while (settings->map[(int)i / CBSZ][(int)ii / CBSZ] != '1')
		{
			i = i + sin(view_start);
//			printf ("\ni = %d ii = %d", i, ii);
			ii = ii + cos(view_start);
			mlx_pixel_put(settings->mlx_ptr, settings->window_ptr, ii, i, 0xff00);
		}
		view_start += M_PI_2 / 1000;
		ii = settings->location_x;
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
				color = 0xff; //blue
			else if (settings->map[i][ii] == ' ')
				color = 0x0; // black
			else if (settings->map[i][ii] == '2')
				color = 0xff00; //green
			else if (settings->map[i][ii] == '0')
				color = 0xffffff; 
			pixel_map(settings, x, y, color);
			x += CBSZ;
			ii++;
		}
		i++;
		y += CBSZ;
	}
	pixel_hero (settings, color);
}

int	close_window(int keycode, t_settings *settings)
{
	if (keycode == 65307) // esc
	{
		mlx_destroy_window(settings->mlx_ptr, settings->window_ptr);
		exit(1);
	}
	if (keycode == 119) // w
	{
		settings->location_y += sin(settings->orientation) * CBSZ / 4;
		settings->location_x += cos(settings->orientation) * CBSZ / 4;
	} 
	if (keycode == 115) // s 
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
	mlx_clear_window(settings->mlx_ptr, settings->window_ptr);
	map_hero_draw(settings);
	return(0);
}

void	init_window(t_settings *settings)
{
	settings->mlx_ptr = mlx_init();
	settings->window_ptr = mlx_new_window(settings->mlx_ptr, settings->resol_x, settings->resol_y, "test");
	map_hero_draw(settings);
	mlx_key_hook(settings->window_ptr, close_window, settings);
	mlx_loop(settings->mlx_ptr);
	exit(1);
//	return (0);
}