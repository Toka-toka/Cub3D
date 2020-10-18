# include "../includes/cub3D.h"

int	key_pressed(int keycode, t_settings *settings)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(settings->win->mlx, settings->win->win);
		exit(1);
	}
	if (keycode == W || keycode == UP)
		settings->actions->move_forward = 1;
	if (keycode == S || keycode == DOWN)
		settings->actions->move_backward = 1;
	if (keycode == A)
		settings->actions->move_left = 1;
	if (keycode == D)
		settings->actions->move_right = 1;
	if (keycode == LEFT)
		settings->actions->turn_left = 1;
	if (keycode == RIGHT)
		settings->actions->turn_right = 1;
	return(0);
}

int	key_released(int keycode, t_settings *settings)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(settings->win->mlx, settings->win->win);
		exit(1);
	}
	if (keycode == W || keycode == UP)
		settings->actions->move_forward = 0;
	if (keycode == S || keycode == DOWN)
		settings->actions->move_backward = 0;
	if (keycode == A)
		settings->actions->move_left = 0;
	if (keycode == D)
		settings->actions->move_right = 0;
	if (keycode == LEFT)
		settings->actions->turn_left = 0;
	if (keycode == RIGHT)
		settings->actions->turn_right = 0;
	return(0);
}

int	actions_call(t_settings *settings)
{
	if (settings->actions->move_forward == 1)
		move_forward_backward(settings, settings->location_y, settings->location_x, SPEED);
	if (settings->actions->move_backward == 1)
		move_forward_backward(settings, settings->location_y, settings->location_x, -SPEED);
	if (settings->actions->move_left == 1)
		move_left_right(settings, settings->location_y, settings->location_x, SPEED / 2);
	if (settings->actions->move_right == 1)
		move_left_right(settings, settings->location_y, settings->location_x, -SPEED / 2);
	if (settings->actions->turn_left == 1)
		turn(settings, M_PI / 90);
	if (settings->actions->turn_right == 1)
		turn(settings, - M_PI / 90);
	ray_emission(settings);
	sprite_sort(settings);
	mlx_put_image_to_window(settings->win->mlx, settings->win->win, settings->win->img, 0, 0);
	mlx_do_sync(settings->win->mlx);
	return(0);
}