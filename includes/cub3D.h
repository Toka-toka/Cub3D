/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmitchel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 00:54:14 by jmitchel          #+#    #+#             */
/*   Updated: 2020/05/26 00:54:16 by jmitchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h"
# include <fcntl.h>
//# include <stdio.h>

typedef	struct		s_settings
{
	char            save_flag;
    int				resol_x;
    int				resol_y;
    char            *path_no;
    char            *path_so;
    char            *path_we;
    char            *path_ea;
    char            *path_s;
    int             color_f[3];
    int             color_c[3];
    char            **map;
    char            orientation_flag;
}					t_settings;

typedef struct		s_list
{
	char			*content;
    int			    len;
	struct s_list	*next;
}					t_list;

int		main(int argc, char** argv);
void	read_settings(int fd, t_settings *settings);
int		error(int err);
void	free_char_arr(void **arr);

#endif
