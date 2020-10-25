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

# FLAGS = -Wall -Wextra -Werror

FLAGS = -Wall

NAME = cub3D

INCLIB=../../../../lib

HEADER = includes/cub3d.h

SRC = src/*.c

OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	make -C libft
#	cp libft/libft.a .
	gcc $(FLAGS) -g -o $(NAME) $(SRC) libft/libft.a -Lminilibx-linux -lmlx -lXext -lX11 -lm

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

mac: 
	gcc $(FLAGS) -g -o $(NAME) $(SRC) libft/libft.a -lmlx -framework OpenGL -framework AppKit

bonus: all
