# include "../includes/cub3D.h"

void check_location (t_settings *settings, float new_loc_y, float new_loc_x)
{
	if (settings->map[(int)new_loc_y / CBSZ][(int)settings->location_x / CBSZ] != '1')
		settings->location_y = new_loc_y;
	if (settings->map[(int)settings->location_y / CBSZ][(int)new_loc_x / CBSZ] != '1')
		settings->location_x = new_loc_x;
}

void	move_forward(t_settings *settings)
{
	float new_loc_y;
	float new_loc_x;
	
	new_loc_y = settings->location_y;
	new_loc_x = settings->location_x;
	new_loc_y -= sin(settings->orientation) * CBSZ / 8;
	new_loc_x += cos(settings->orientation) * CBSZ / 8;
	check_location (settings, new_loc_y, new_loc_x);
}

void	move_backward(t_settings *settings)
{
	float new_loc_y;
	float new_loc_x;
	
	new_loc_y = settings->location_y;
	new_loc_x = settings->location_x;
	new_loc_y += sin(settings->orientation) * CBSZ / 8;
	new_loc_x -= cos(settings->orientation) * CBSZ / 8;
	check_location (settings, new_loc_y, new_loc_x);
}

void	move_left(t_settings *settings)
{
	float new_loc_y;
	float new_loc_x;
	
	new_loc_y = settings->location_y;
	new_loc_x = settings->location_x;
	new_loc_y -= cos(settings->orientation) * CBSZ / 8;
	new_loc_x += sin(settings->orientation) * CBSZ / 8;
	check_location (settings, new_loc_y, new_loc_x);
}

void	move_right(t_settings *settings)
{
	float new_loc_y;
	float new_loc_x;	
	
	new_loc_y = settings->location_y;
	new_loc_x = settings->location_x;
	new_loc_y += cos(settings->orientation) * CBSZ / 8;
	new_loc_x -= sin(settings->orientation) * CBSZ / 8;
	check_location (settings, new_loc_y, new_loc_x);
}

void	turn(t_settings *settings)
{
	if (settings->actions->turn_right == 1)
		settings->orientation -= M_PI / 90;
	else if (settings->actions->turn_left == 1)
		settings->orientation += M_PI / 90;
	if (settings->orientation > M_PI * 2)
		settings->orientation = 0;
	else if (settings->orientation < 0)
		settings->orientation = M_PI * 2;
}