# include "../includes/cub3D.h"

void	pixel(t_settings *settings, int x, int y, int color)
{
	int i = 0;
	int x_start = 0;

	x_start = x;
	while (i < 20)
	{
		x = x_start;
		while (x - x_start < 20)
		{		
			mlx_pixel_put(settings->mlx_ptr, settings->window_ptr, x, y, color);
			x++;
		}
		i++;
		y++;
	}
}

void	init_window(t_settings *settings)
{
	int i = 0;
	int ii = 0;
	int x = 0;
	int y = 0;
	int color;
	settings->mlx_ptr = mlx_init();
	settings->window_ptr = mlx_new_window(settings->mlx_ptr, 1000, 1000, "test");
//	while (i != 250)
//	{
//		ii = 100;
//		while (ii != 250)
//		{
//			mlx_pixel_put(settings->mlx_ptr, settings->window_ptr, i, ii, 0xffdead);
//			ii++;
//		}
//		i++;
//	}
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
			else color = 0xffff00; //yellow
			pixel(settings, x, y, color);
			x += 20;
			ii++;
		}
		i++;
		y += 20;
	}
	mlx_loop(settings->mlx_ptr);
//	return (0);
}
