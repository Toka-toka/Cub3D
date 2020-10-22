#include "../includes/cub3D.h"

void	cuba_libre(t_settings *set)
{
	int i;
	t_sprite	*ptr;
	
	if (set == NULL)
		exit (-1);
	i = 0;
	if (set->map != NULL)
		free_char_arr((void **)set->map);
//	printf(NULL);
	free(set->win->mlx);
	i = 0;
	while (set->sprite != NULL)
	{
		ptr = set->sprite;
		set->sprite = set->sprite->next;
		free(ptr);
	}
	while (i < 5)
	{
		if (set->xpm[i].addr != NULL)
//			free_char_arr((void **)set->xpm[i].addr);
		i++;
	}
	if (set->ray->all_dist != NULL)
		free(set->ray->all_dist);
}

int		error(char *error, t_settings *set)
{
	write(2, "Error\n", 6);
	while (*error)
		write(2, error++, 1);
	cuba_libre(set);
	exit(-1);
}

void	free_char_arr(void **arr)
{
	int i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	init_struct(t_settings *set)
{
	static t_win		win;
	static t_actions	actions;
	static t_player		plr;
	static t_ray		ray;
	int					i;

	i = -1;
	set->win = &win;
	set->sprite = NULL;
	set->actions = &actions;
	set->map = NULL;
	set->plr = &plr;
	set->ray = &ray;
	set->resol_x = -1;
	set->resol_y = -1;
	while(5 > i++)
		set->xpm[i].addr = NULL;
	if ((set->win->mlx = mlx_init()) == NULL)
		error("Mxl init problem", NULL);
}

int		init_mlx_magic(t_win *win, int resol_x, int resol_y, char *name)
{
	name = ft_strjoin("Cub3d:", name);
	win->win = mlx_new_window(win->mlx, resol_x, resol_y, name);
	if (win->mlx == NULL || win->win == NULL)
		error("Mxl init problem", NULL);
	win->img = mlx_new_image(win->mlx, resol_x, resol_y);
	win->addr = mlx_get_data_addr(win->img, &win->bpp, &win->line_l, &win->en);
	win->constant = (float)resol_x / 2 / tan(M_PI / 3);
	free(name);
	return (0);
}

int		exit_game(int key, t_settings *set)
{
	write(1, "Good bye!\n", 10);
	cuba_libre(set);
	exit(0);
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
	set->save_flag = argc == 3 ? '1' : '0';
	return (fd);
}

int		main(int argc, char **argv)
{
	t_settings	set;

	init_struct(&set);
	read_settings(check_agr(&set, argc, argv), &set);
	init_mlx_magic(set.win, set.resol_x, set.resol_y, argv[1]);
	set.ray->all_dist = (float *)malloc(sizeof(float) * set.resol_x);
	if (set.ray->all_dist == NULL)
		error("Malloc problem (main", &set);
	set.ray->step = M_PI / 3 / set.resol_x;
	mlx_hook(set.win->win, 17, 1L << 17, exit_game, &set);
	mlx_hook(set.win->win, 2, 1L << 0, key_pressed, &set);
	mlx_hook(set.win->win, 3, 1L << 1, key_released, &set);
	mlx_loop_hook(set.win->mlx, actions_call, &set);
	mlx_loop(set.win->mlx);
	return (0);
}
