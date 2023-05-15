# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 19:45:58 by gyopark           #+#    #+#              #
#    Updated: 2023/05/15 15:02:02 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -o3 -g3 #-fsanitize=address
MLX         = -L./mlx -lmlx -framework OpenGL -framework AppKit
MLXDIR      = ./mlx
LIBFTDIR    = ./libft
LIBFT       = libft.a

SRCS_MAN    = main.c                    \
			  map_setting.c             \
			  map_valid.c               \
			  map_direction.c           \
			  map_color.c               \
			  map2_press.c              \
			  map2_cast.c				\
			  map2_cast_init.c			\
			  map2_player.c				\
			  map2_ray.c				\
			  map3_render.c				\
			  gnl/get_next_line.c       \
			  utils.c                   \
			  utils2.c

OBJS_MAN    = ${SRCS_MAN:.c=.o}

$(NAME) : $(OBJS_MAN)
		rm -f $(NAME)
		make clean -C $(MLXDIR)
		make fclean -C $(LIBFTDIR)  
		make all -C $(MLXDIR)
		make all -C $(LIBFTDIR)
		$(CC) $(CFLAGS) $(MLX) $^ $(LIBFTDIR)/$(LIBFT) -o $(NAME)

all : $(NAME)

fclean : clean
		rm -f $(NAME)

clean :
		rm -f $(OBJS_MAN) 
		make clean -C $(MLXDIR)
		make clean -C $(LIBFTDIR)

re : 
	make fclean 
	make all

.PHONY : fclean clean re all
