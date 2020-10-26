#include "../includes/cub3d.h"

int		write_head(t_settings *set, int fd)
{
	if (write(fd, "BM", 2) != 2 ||
	write(fd, &set->bmp_head[0], 4) != 4 ||
	write(fd, &set->bmp_head[1], 4) != 4 ||
	write(fd, &set->bmp_head[2], 4) != 4 ||
	write(fd, &set->bmp_head[3], 4) != 4 ||
	write(fd, &set->bmp_head[4], 4) != 4 ||
	write(fd, &set->bmp_head[5], 4) != 4 ||
	write(fd, &set->bmp_head[6], 2) != 2 ||
	write(fd, &set->bmp_head[7], 2) != 2 ||
	write(fd, &set->bmp_head[8], 4) != 4 ||
	write(fd, &set->bmp_head[8], 4) != 4 ||
	write(fd, &set->bmp_head[8], 4) != 4 ||
	write(fd, &set->bmp_head[8], 4) != 4 ||
	write(fd, &set->bmp_head[8], 4) != 4 ||
	write(fd, &set->bmp_head[8], 4) != 4)
		return (-1);
	else
		return (0);
}

void		init_value(t_settings *set)
{
	set->bmp_head[0] = (set->x * set->y * 4) + 54;
	set->bmp_head[1] = 0;
	set->bmp_head[2] = 54;
	set->bmp_head[3] = 40;
	set->bmp_head[4] = set->x;
	set->bmp_head[5] = -set->y;
	set->bmp_head[6] = 1;
	set->bmp_head[7] = 32;
	set->bmp_head[8] = 0;
}

void		save_picture(t_settings *set)
{
	int		fd;
	int		size;

	if ((fd = open("cub3d.bmp", O_CREAT | O_WRONLY |
		O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
		error("Problem with file for write", set);
	ray_emission(set, set->plr->pov + M_PI / 6, 0);
	sprite_finder(set);
	init_value(set);
	size = set->x * set->y * 4;
	if (write_head(set, fd) != 0 ||
		write(fd, set->win->addr, size) != size)
		error("Write error", set);
	close(fd);
    write(1, "Picture saved in file 'screen.bmp'\n", 36);
    exit_game(ESC, set);
}
