# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sedric <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/14 17:29:46 by sedric            #+#    #+#              #
#    Updated: 2020/05/25 23:56:10 by sedric           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAGS = -Wall -Wextra -Werror

NAME = cub3D

SRC = 	src/check_map.c\
		src/draw.c\
		src/exit.c\
		src/key_events.c\
		src/load_settings.c\
		src/main.c\
		src/move.c\
		src/raycasting.c\
		src/sprite.c\
		src/textures.c\
		src/save.c\

OBJ = $(SRC:.c=.o)

MLXFLAG = -L. -lmlx -lXext -lX11 -lm

LIBFT = libft.a

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C mlx
	mv mlx/libmlx.a .
	make -C libft
	mv libft/$(LIBFT) .
	gcc $(FLAGS) -g -o $(NAME) $(OBJ) $(LIBFT) $(MLXFLAG)

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C mlx clean

fclean: clean
	rm -f $(NAME) libmlx.a libft.a cub3D.bmp

re: fclean all

bonus: all

.PHONY: all clean fclean re