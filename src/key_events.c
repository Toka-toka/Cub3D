# include "../includes/cub3D.h"

int	key_pressed(int keycode, t_settings *settings)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(settings->win_3d->mlx_ptr, settings->win_3d->window_ptr);
		mlx_destroy_window(settings->mlx_ptr, settings->window_ptr);
		exit(1);
	}
	if (keycode == 119) //|| keycode == UP)
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
	if (keycode == 119) // || keycode == UP)
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
		move_forward(settings);
	if (settings->actions->move_backward == 1)
		move_backward(settings);
	if (settings->actions->move_left == 1)
		move_left(settings);
	if (settings->actions->move_right == 1)
		move_right(settings);
	if (settings->actions->turn_left == 1 || settings->actions->turn_right == 1)
		turn(settings);
	mlx_clear_window(settings->win_3d->mlx_ptr, settings->window_ptr);
	map_hero_draw(settings);
	return(0);
}