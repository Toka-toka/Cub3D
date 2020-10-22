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

int		exit_game(int key, t_settings *set)
{
	write(1, "Good bye!\n", 10);
	cuba_libre(set);
	exit(0);
	return (0);
}