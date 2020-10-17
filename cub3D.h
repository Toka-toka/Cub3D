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

# include "../minilibx_mac/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
//# include <stdio.h>

#define _USE_MATH_DEFINES

# ifndef CBSZ
#  define CBSZ 32
# endif

# define W  13// 119
# define A  0//100
# define S 1//115
# define D 2//97
# define UP 65362
# define DOWN 65364
# define LEFT 123//65361
# define RIGHT 124//65363
# define ESC 53//65307

typedef struct	s_win
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*addr;
	int			line_l;
	int			bpp;
	int			en;
	float		constant;
}				  t_win;

typedef struct			s_actions
{
	int					move_forward;
	int					move_backward;
	int					move_left;
	int					move_right;
	int					turn_left;
	int					turn_right;
}						t_actions;

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
    int             max_x;
    int             max_y;
    char            orientation_flag;
    float           orientation;
    float           location_x;
    float           location_y;
    t_win		    *win;
    t_actions      	*actions;
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
void	init_window(t_settings *settings);
int     key_pressed_released(int keycode, t_settings *settings);
int 	actions_call(t_settings *settings);
void    check_location (t_settings *settings, float new_loc_y, float new_loc_x);
void	move_forward(t_settings *settings);
void	move_backward(t_settings *settings);
void	move_left(t_settings *settings);
void	move_right(t_settings *settings);
void	turn(t_settings *settings);
void	map_hero_draw(t_settings *settings);
void	ray_emission(t_settings *settings);
void	column_draw(float distanse, t_settings *settings, char orientation, int x);
void	my_mlx_pixel_put(t_settings *settings, int x, int y, int color);

#endif
