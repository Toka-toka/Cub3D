# include "../includes/cub3D.h"

void		error_print(char *error)
{
//	int i;
	
//	i = 0;
	write(2, "Error\n", 6);
	while (*error)
		write(2, error++, 1);
}

int		error(int err) // TODO: передавать ошибки при вызове функций
{
	char	*error[24];

	error[0] = "Invalid quantity of arguments\n";
	error[1] = "Format of the 1-st argument is not '.cub'\n";
	error[2] = "Second argument is not '––save'\n";
	error[3] = "File can not open\n";
	error[4] = "Malloc problem\n";
	error[5] = "Some settings are missing\n";
	error[6] = "Invalid name or quantity of settings in file .cub\n";
	error[7] = "Too many settings in file .cub or invalid 1-st line of a map\n";
	error[8] = "Double R\n";
	error[9] = "Too much \\ less parametrs for R\n";
	error[10] = "Wrong simbols in R\n";
	error[11] = "There is no map in file .cub?!\n";
	error[12] = "Something wrong whis list\n";
	error[13] = "The map is not closed\n";
	error[14] = "The last line of a map is invalid\n";
	error[15] = "Invalid symbol in map\n";
	error[16] = "Double camera plase\n";
	error[17] = "No camera plase\n";
	error[18] = "Wrong way to texture\n";
	error[19] = "Double path\n";
	error[20] = "Too much \\ less parametrs for color of floor \\ ceiling\n";
	error[21] = "Wront symbols in color of floor \\ ceiling\n";
	error[22] = "Incorrect color definition \\ ceiling\n";
	error[23] = "Size of the textures is not 64x64, i can't init magic\n";

	error_print(error[err]);
	exit(-1);
}

void	free_char_arr(void **arr)
{
	int i;
	
	i = 0;
	while(arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	struct_clear(t_settings *settings)
{
	settings->resol_x = -1;
  	settings->resol_y = -1;
    settings->path_no = NULL;
    settings->path_so = NULL;
    settings->path_we = NULL;
    settings->path_ea = NULL;
    settings->path_s = NULL;
	settings->orientation_flag = 0;
	settings->actions->move_forward = 0;
	settings->actions->move_backward = 0;
	settings->actions->move_left = 0;
	settings->actions->move_right = 0;
	settings->actions->turn_left = 0;
	settings->actions->turn_right = 0;
//    settings->color_f[3] = NULL;
 //   settings->color_c[3] = NULL;
}

void	struct_printclear(t_settings *settings)
{
	int i = 0;
	
	printf("\n____________________________________struct_check_________________________________\n");
	printf("save_flag = %c\n", settings->save_flag);
	printf("resol_x = %d\n", settings->resol_x);
	printf("resol_y = %d\n", settings->resol_y);
	printf("path_no = %s\n", settings->path_no);
	printf("path_so = %s\n", settings->path_so);
	printf("path_we = %s\n", settings->path_we);
	printf("path_ea = %s\n", settings->path_ea);
	printf("path_s = %s\n", settings->path_s);
	while (i < 3)
	{
		printf("color_f[%d] = %d\n", i, settings->color_f[i]);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		printf("color_c[%d] = %d\n", i, settings->color_c[i]);
		i++;
	}
	i = 0;
    while (settings->map[i] != NULL)
	{
		printf("map[%d] = %s\n", i, settings->map[i]);
		i++;
	}
	printf("orientation_flag = %c\n", settings->orientation_flag);
	free(settings->path_no);
	free(settings->path_so);
	free(settings->path_we);
	free(settings->path_ea);
	free(settings->path_s);
	free_char_arr((void**)settings->map);
}

int			init_mlx_magic(t_settings *settings, int resol_x, int resol_y, char *name)
{
	name = ft_strjoin("Cub3d:", name);
	settings->win->win = mlx_new_window(settings->win->mlx, resol_x, resol_y, name);
	if (settings->win->mlx == NULL || settings->win->win == NULL)
		return(-1);
	settings->win->img = mlx_new_image(settings->win->mlx, resol_x, resol_y);
	settings->win->addr = mlx_get_data_addr(settings->win->img, &settings->win->bpp, &settings->win->line_l, &settings->win->en);
	settings->win->constant = (float)settings->resol_x / 2 / tan(M_PI / 3);
	settings->rays = (float *)malloc(sizeof(float) * resol_x);
	free(name);
	return(0);
}

int			main(int argc, char** argv)
{
	int		i;
	int		fd;
	t_settings settings;
	t_win		win;
	t_actions	actions;
	t_xpm xpm;

	settings.sprite = NULL;
	settings.xpm = &xpm; // TODO: убрать отсюда
	xpm.addr = NULL;
	settings.win = &win;
	settings.actions = &actions;
	settings.win->mlx = mlx_init();
	if (argc < 2 || argc > 3) // TODO: перенести в отделную функцию
		error(0);
	if ((i = ft_strlen(argv[1])) < 4)
		error(1);
	i -= 4;
	if ((ft_strncmp(argv[1] + i, ".cub", 5)) != 0)
		error(1);
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 7) != 0))
		error(2);
	if((fd = open(argv[1], O_APPEND)) == -1)
		error(3);
	settings.save_flag = argc == 3 ? '1' : '0';
	struct_clear(&settings);
	read_settings(fd, &settings);
	argv[1][i] = '\0';
	init_mlx_magic(&settings, settings.resol_x, settings.resol_y, argv[1]);
//	struct_printclear(&settings); // TODO: настроить очистку памяти при выходе
	actions_call (&settings);
	mlx_put_image_to_window(settings.win->mlx, settings.win->win, settings.win->img, 0, 0);
	mlx_hook(settings.win->win, 2, 1L << 0, key_pressed, &settings);
	mlx_hook(settings.win->win, 3, 1L << 1, key_released, &settings);
	mlx_loop_hook(settings.win->mlx, actions_call, &settings);
	mlx_loop(settings.win->mlx);
	mlx_clear_window(win.mlx, win.win); // TODO: должна работать только при выходе
	return (0);
}