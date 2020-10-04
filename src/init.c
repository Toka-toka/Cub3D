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

	int floor_h;
	int ceiling_h;
	float column_h;
	int column_y;
	float xpm_scale;
	int y;

	y = 0;
	column_h = 32 / distanse * settings->win->constant;
	xpm_scale = column_h / settings->xpm->height;
	if (column_h >= settings->resol_y)
	{
		floor_h = 0;
		ceiling_h = 0;
		column_y = (settings->resol_y - column_h) / 2;
		column_h = column_y + settings->resol_y;
	}
	else
	{
		floor_h = (settings->resol_y - column_h) / 2;
		ceiling_h = floor_h;
		column_y = 0;
	}
	while (floor_h > 0)
	{
		my_mlx_pixel_put(settings, x, y, 0x87ceeb);
		floor_h--;
		y++;
	}
	while (column_y < column_h)
	{
		my_mlx_pixel_put(settings, x, y, 0xff0000);
		column_y++;
		y++;
	}
	while (ceiling_h > 0)
	{
		my_mlx_pixel_put(settings, x, y, 0x708090);
		y++;
		ceiling_h--;
	}
}