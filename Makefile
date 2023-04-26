# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 19:45:58 by gyopark           #+#    #+#              #
#    Updated: 2023/04/26 14:26:24 by youngski         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = cub3d

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3 -fsanitize=address
MLX         = -L./mlx -lmlx -framework OpenGL -framework AppKit
MLXDIR      = ./mlx
LIBFTDIR    = ./libft
LIBFT       = libft.a

SRCS_MAN    = main.c                    \
			  map_setting.c             \
			  map_valid.c               \
			  map_direction.c           \
			  map_color.c               \
			  map_mlx.c                 \
			  utils.c                   \
			  utils2.c                  \
			  map_cast.c				\
			  map_cast_init.c			\
			  gnl/get_next_line.c       \
			  hooking.c

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
