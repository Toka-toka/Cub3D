/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:35:39 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:35:42 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_location(t_settings *set, float new_y, float new_x)
{
	int y;
	int x;

	y = new_y / CBSZ;
	x = new_x / CBSZ;
	if (set->map[y][(int)set->plr->x / CBSZ] != '1')
		set->plr->y = new_y;
	if (set->map[(int)set->plr->y / CBSZ][x] != '1')
		set->plr->x = new_x;
}

void	move_forward_backward(t_settings *set, float y, float x, float spd)
{
	y -= sin(set->plr->pov) * spd;
	x += cos(set->plr->pov) * spd;
	check_location(set, y, x);
}

void	move_left_right(t_settings *set, float y, float x, float spd)
{
	y -= cos(set->plr->pov) * spd;
	x -= sin(set->plr->pov) * spd;
	check_location(set, y, x);
}

void	turn(t_settings *set, float spd)
{
	set->plr->pov += spd;
	if (set->plr->pov > M_PI * 2)
		set->plr->pov = 0;
	else if (set->plr->pov < 0)
		set->plr->pov = M_PI * 2;
}
