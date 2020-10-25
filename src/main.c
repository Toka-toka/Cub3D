/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedric <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:35:32 by sedric            #+#    #+#             */
/*   Updated: 2020/10/22 22:35:34 by sedric           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	pars_plr(t_settings *set, int i, int ii)
{
	if (set->plr->pov != 0)
		error("Double camera plase\n", set);
	set->plr->x = ii * CBSZ + CBSZ / 2;
	set->plr->y = i * CBSZ + CBSZ / 2;
	if (set->map[i][ii] == 'N')
		set->plr->pov = M_PI / 2;
	if (set->map[i][ii] == 'S')
		set->plr->pov = M_PI * 3 / 2;
	if (set->map[i][ii] == 'E')
		set->plr->pov = 2 * M_PI;
	if (set->map[i][ii] == 'W')
		set->plr->pov = M_PI;
	set->map[i][ii] = '0';
}

void	init_struct(t_settings *set)
{
	static t_win		win;
	static t_player		plr;
	static t_ray		ray;
	int					i;

	i = -1;
	set->win = &win;
	set->sprite = NULL;
	set->map = NULL;
	set->plr = &plr;
	set->ray = &ray;
	set->x = -1;
	set->y = -1;
	set->sprite = NULL;
	set->max_x = 0;
	set->max_y = 1;
	while (i < 5)
		set->xpm[i++].addr = NULL;
	if ((set->win->mlx = mlx_init()) == NULL)
		error("Mxl init problem", NULL);
}

int		init_mlx_magic(t_settings *set, t_win *win, char *name)
{
	static t_actions	actions;

	set->actions = &actions;
	if (!(name = ft_strjoin("Cub3d:", name)))
		error("Malloc problem (init_mlx_magic)", set);
	win->win = mlx_new_window(win->mlx, set->x, set->y, name);
	if (win->mlx == NULL || win->win == NULL)
		error("Mxl init problem", NULL);
	win->img = mlx_new_image(win->mlx, set->x, set->y);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
	if (win->img == NULL || win->addr == NULL)
		error("Mxl init problem", NULL);
	win->constant = (float)set->x / 2 / tan(M_PI / 3);
	set->ray->all_dist = (float *)malloc(sizeof(float) * set->x);
	if (set->ray->all_dist == NULL)
		error("Malloc problem (init_mlx_magic)", set);
	set->ray->step = M_PI / 3 / set->x;
	free(name);
	return (0);
}

int		check_agr(t_settings *set, int argc, char **argv)
{
	int	i;
	int	fd;

	if (argc < 2 || argc > 3)
		error("Invalid quantity of arguments\n", set);
	if ((i = ft_strlen(argv[1])) < 4)
		error("1-st argument is not '.cub'\n", set);
	i -= 4;
	if ((ft_strncmp(argv[1] + i, ".cub", 5)) != 0)
		error("1-st argument is not '.cub'\n", set);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 7) != 0))
		error("Second argument is not '--save'\n", set);
	if ((fd = open(argv[1], O_APPEND)) == -1)
		error("File cannot be opened\n", set);
	argv[1][i] = '\0';
	set->save_flag = argc == 3 ? 1 : 0;
	return (fd);
}

int		main(int argc, char **argv)
{
	t_settings	set;

	init_struct(&set);
	read_settings(check_agr(&set, argc, argv), &set);
	init_mlx_magic(&set, set.win, argv[1]);
	if (set.save_flag == 1)
	{
		actions_call(&set);
		exit_game(0, &set);
	}
	mlx_hook(set.win->win, 17, 1L << 17, exit_game, &set);
	mlx_hook(set.win->win, 2, 1L << 0, key_pressed, &set);
	mlx_hook(set.win->win, 3, 1L << 1, key_released, &set);
	mlx_loop_hook(set.win->mlx, actions_call, &set);
	mlx_loop(set.win->mlx);
	return (0);
}
