# include "../includes/cub3D.h"

void		error_print(char *error)
{
//	int i;
	
//	i = 0;
	write(2, "Error\n", 6);
	while (*error)
		write(2, error++, 1);
}

int		error(int err)
{
	char	*error[22];

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

int			main(int argc, char** argv)
{
	int		i;
	int		fd;
	t_settings settings;
	
	if (argc < 2 || argc > 3)
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
	printf("save_flag = %c", settings.save_flag);
	struct_clear(&settings);
	read_settings(fd, &settings);
//	struct_printclear(&settings);
	init_window(&settings);
	return (0);
}