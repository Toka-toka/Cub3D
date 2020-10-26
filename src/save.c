
#include "../includes/cub3d.h"

void	bmp_set_image(t_settings *set, int fd)
{
	int				x;
	int				y;
	unsigned char	*color;

	y = set->y;
	while (--y >= 0)
	{
		x = -1;
		while (++x < set->x)
		{
			color = (unsigned char*)set->win->addr;
			write(fd, &color[(y * set->x + x) * set->win->bpp / 8], 4);
		}
	}
}

void	bmp_header(t_settings *set, int fd)
{
	int		local;
	local = 40;
	write(fd, &local, 4);
	write(fd, &set->x, 4);
	write(fd, &set->y, 4);
	local = 1;
	write(fd, &local, 2);
	write(fd, &set->win->bpp, 2);
	local = -1;
	while (++local < 28)
		write(fd, "\0", 1);
	local = 40;
	write(fd, &local, 4);
	write(fd, &set->x, 4);
	write(fd, &set->y, 4);
	local = 1;
	write(fd, &local, 2);
	write(fd, &set->win->bpp, 2);
	local = -1;
	while (++local < 28)
		write(fd, "\0", 1);
}

void			create_bmp(t_settings *set)
{
	int		fd;
	int		f_size;
	int		f_first;

	ray_emission(set, set->plr->pov + M_PI / 6, 0);
	sprite_finder(set);
	if ((fd = open("cub3D.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU)) == -1)
		error("File 'cub3D.bmp' didnt create", set);
	f_first = 14 + 40 + 4;
	f_size = f_first + set->x * set->y * 4;
	write(fd, "BM", 2);
	write(fd, &f_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &f_first, 4);
	bmp_header(set, fd);
	bmp_set_image(set, fd);
	close(fd);
	exit(0);
}
