#include "../includes/cub3D.h"

void	check_location(t_settings *set, float new_y, float new_x)
{
	int y;
	int x;

	y = new_y / CBSZ;
	x = new_x / CBSZ;
	if (set->map[y][(int)set->location_x / CBSZ] != '1')
		set->location_y = new_y;
	if (set->map[(int)set->location_y / CBSZ][x] != '1')
		set->location_x = new_x;
}

void	move_forward_backward(t_settings *set, float y, float x, float spd)
{
	y -= sin(set->orientation) * spd;
	x += cos(set->orientation) * spd;
	check_location(set, y, x);
}

void	move_left_right(t_settings *set, float y, float x, float spd)
{
	y -= cos(set->orientation) * spd;
	x -= sin(set->orientation) * spd;
	check_location(set, y, x);
}

void	turn(t_settings *set, float spd)
{
	set->orientation += spd;
	if (set->orientation > M_PI * 2)
		set->orientation = 0;
	else if (set->orientation < 0)
		set->orientation = M_PI * 2;
}
