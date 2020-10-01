# include "../includes/cub3D.h"

int	key_pressed_released(int keycode, t_settings *settings)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(settings->win->mlx, settings->win->win);
		exit(1);
	}
	if (keycode == W || keycode == UP)
		settings->actions->move_forward = settings->actions->move_forward == 0 ? 1 : 0;
	if (keycode == S || keycode == DOWN)
		settings->actions->move_backward = settings->actions->move_backward == 0 ? 1 : 0;
	if (keycode == A)
		settings->actions->move_left = settings->actions->move_left == 0 ? 1 : 0;
	if (keycode == D)
		settings->actions->move_right = settings->actions->move_right == 0 ? 1 : 0;
	if (keycode == LEFT)
		settings->actions->turn_left = settings->actions->turn_left == 0 ? 1 : 0;
	if (keycode == RIGHT)
		settings->actions->turn_right = settings->actions->turn_right == 0 ? 1 : 0;
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
//	printf("orientation = %f/n", settings->orientation);
	mlx_clear_window(settings->win->mlx, settings->win->win);
	ray_emission(settings);
	return(0);
}