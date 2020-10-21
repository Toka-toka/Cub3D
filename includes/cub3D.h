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

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <math.h>
# include <limits.h>
//# include <stdio.h>

#define _USE_MATH_DEFINES

# ifndef CBSZ
#  define CBSZ 1024
# endif

# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define SPEED CBSZ / 7
/*
# define W  13 // 119
# define A  0 //100
# define S 1 //115
# define D 2 //97
# define UP 65362
# define DOWN 65364
# define LEFT 123 //65361
# define RIGHT 124 //65363
# define ESC 53 //65307
*/

typedef struct	s_ray
{
    float       step;
    float       angle;
    float       tg;
    float       x_step;
    float       y_step;
    int         x_midl;
    int         y_midl;
    float       dist;
	int         side;
    int         plase;
    float       *all_dist;
}				  t_ray;

typedef struct	s_xpm
{
    void		*img; // нужна
    int         width;
    float       wid_scale;
    int         height;
	int 		**addr;
}				  t_xpm;

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

typedef struct		s_sprite
{
	float           x;
    float           y;
    float           angle;
    float           dist;
    int 		    **addr;
	struct s_sprite	*next;
}					t_sprite;

typedef	struct		s_player
{
    float           x;
    float           y;
    float           pov;
}					t_player;

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
    t_win		    *win;
    t_actions      	*actions;
    t_xpm           xpm[5];
    t_sprite        *sprite;
    t_player        *plr;
    t_ray           *ray;
}					t_settings;

typedef struct		s_list
{
	char			*content;
    int			    len;
	struct s_list	*next;
}					t_list;

int		main(int argc, char** argv);
void	read_settings(int fd, t_settings *settings);
int		error(char *err, t_settings *settings);
void	free_char_arr(void **arr);
void	init_window(t_settings *settings);
int     key_pressed(int keycode, t_settings *settings);
int     key_released(int keycode, t_settings *settings);
int 	actions_call(t_settings *settings);
void	move_forward_backward(t_settings *settings, float new_loc_y, float new_loc_x, float speed);
void	move_left_right(t_settings *settings, float new_loc_y, float new_loc_x, float speed);
void	turn(t_settings *set, float spd);
void	map_hero_draw(t_settings *settings);
void	ray_emission(t_settings *set, float	view_start, int i);
void    column_draw(t_settings *settings, float distanse, int side, int plase);
void	my_mlx_pixel_put(t_settings *settings, int x, int y, int color);
void	load_textures(t_settings *settings, t_xpm *xpm, char *line, int side);
void	new_sprite(int x, int y, t_settings *settings);
void	sprite_sort(t_settings *settings);
void	cuba_libre(t_settings *set);
void	pars_map(t_settings *settings, int len_max, int lists, t_list *head);
t_list	*new_list(char *line);

#endif
