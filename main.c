
# include "cub3D.h"

int		error(int err)
{
	if (err == 1)
		write(2, "NO ARGV", 7);
	if (err == 2)
		write(2, "File is ompty", 13);
	return(-1);
}

int		main(int argc, char** argv)
{
//	int	status;
	int fd;
	char	*line;
	if (argc != 2)
		return(error(1));
	if ((fd = open(argv[1], O_APPEND)) == -1)
		return(error(2));
	get_next_line(fd, &line);
/*	char *line;
	int i;
	i = get_next_line(23, &line);
	printf("%d", i); */
	return (0);
}
