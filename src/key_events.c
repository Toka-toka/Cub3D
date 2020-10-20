#include "../includes/cub3D.h"

int	key_pressed(int keycode, t_settings *set)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(set->win->mlx, set->win->win);
		exit(1);
	}
	if (keycode == W || keycode == UP)
		set->actions->move_forward = 1;
	if (keycode == S || keycode == DOWN)
		set->actions->move_backward = 1;
	if (keycode == A)
		set->actions->move_left = 1;
	if (keycode == D)
		set->actions->move_right = 1;
	if (keycode == LEFT)
		set->actions->turn_left = 1;
	if (keycode == RIGHT)
		set->actions->turn_right = 1;
	return (0);
}

int	key_released(int keycode, t_settings *set)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(set->win->mlx, set->win->win);
		exit(1);
	}
	if (keycode == W || keycode == UP)
		set->actions->move_forward = 0;
	if (keycode == S || keycode == DOWN)
		set->actions->move_backward = 0;
	if (keycode == A)
		set->actions->move_left = 0;
	if (keycode == D)
		set->actions->move_right = 0;
	if (keycode == LEFT)
		set->actions->turn_left = 0;
	if (keycode == RIGHT)
		set->actions->turn_right = 0;
	return (0);
}

int	actions_call(t_settings *set)
{
	mlx_do_sync(set->win->mlx);
	if (set->actions->move_forward == 1)
		move_forward_backward(set, set->plr->y, set->plr->x, SPEED);
	if (set->actions->move_backward == 1)
		move_forward_backward(set, set->plr->y, set->plr->x, -SPEED);
	if (set->actions->move_left == 1)
		move_left_right(set, set->plr->y, set->plr->x, SPEED / 2);
	if (set->actions->move_right == 1)
		move_left_right(set, set->plr->y, set->plr->x, -SPEED / 2);
	if (set->actions->turn_left == 1)
		turn(set, M_PI / 90);
	if (set->actions->turn_right == 1)
		turn(set, -M_PI / 90);
	ray_emission(set, set->plr->pov + M_PI / 6, 0);
	sprite_sort(set);
	mlx_put_image_to_window(set->win->mlx, set->win->win, set->win->img, 0, 0);
	return (0);
}
