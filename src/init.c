# include "../includes/cub3D.h"


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

void	pixel_hero(t_settings *settings, int color)
{
	float y = 0;
	float x = 0;

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
//	y = settings->location_y;
//	x = settings->location_x;
//	while (settings->map[(int)y / CBSZ][(int)x / CBSZ] != '1')
//		{
//			y += sin(settings->orientation);
//			x += cos(settings->orientation);
//			my_mlx_pixel_put(settings, x, y, 0x20b2aa);
//		}
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
			pixel_map(settings, x, y, color);
			x += CBSZ;
			ii++;
		}
		i++;
		y += CBSZ;
	}
	pixel_hero (settings, color);
}

void column_draw(float distanse, t_settings *settings, char orientation, int x)
{
//	static int x;
	int y;
	int y_start_col;
	float height;
	int color;

	if (orientation == 'N')
		color = 0xff0000;
	if (orientation == 'S')
		color = 0xffff00;
	if (orientation == 'W')
		color = 0xffa500;
	if (orientation == 'E')
		color = 0xffc0cb;
	y = 0;
	height = 32 / distanse * settings->win->constant;
	y_start_col = settings->resol_y / 2 - height / 2;
	while (y < settings->resol_y)
	{
		while (y < y_start_col && y < settings->resol_y)
		{
			my_mlx_pixel_put(settings, x, y, 0x87ceeb); 
			y++;
		}
		while (height > 0 && y < settings->resol_y)
		{
			my_mlx_pixel_put(settings, x, y, color); 
			height--;
			y++;
		}
		my_mlx_pixel_put(settings, x, y, 0x708090);
		y++;
	}
//	x++;
//	if (x == settings->resol_x)
//		x = 0;
}
/*
int		color_column(float x, float y)
{
	static int x_prev;
	static int y_prev;
	static char nswe_prev;

	if (remains_by_bits(y + 1, 32) == 0) //&& nswe_prev != 'E')// && (x_prev != (int)x && nswe_prev == 'S'))
	{
		x_prev = (int)x;
		nswe_prev = 'S';
		return(0xffff00); // yellow
	}
	else if (remains_by_bits(x, 32) == 0) // && (y_prev != (int)y && nswe_prev == 'E'))
	{
		y_prev = (int)y;
		nswe_prev = 'E';
		return(0xff0000); // red
	}
	else if (remains_by_bits(y, 32) == 0) // && remains_by_bits(x, 32) != 0)
		return(0xff); // blue
	else if (remains_by_bits(x + 1, 32) == 0)
		return(0xffa500); // orange
}*/