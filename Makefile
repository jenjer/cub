# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/16 19:45:58 by gyopark           #+#    #+#              #
#    Updated: 2023/03/26 18:31:46 by gyopark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g #-fsanitize=address
MLX			= -L./mlx -lmlx -framework OpenGL -framework AppKit
MLXDIR		= ./mlx
FT_PRINTF	= ft_printf
PRINTF_LIB	= libftprintf.a

SRCS_MAN 	= main.c					\
			  map_setting.c				\
			  map_valid.c				\
			  map_direction.c			\
			  map_color.c				\
			  utils.c					\
			  gnl/get_next_line.c		\
			  gnl/get_next_line_utils.c	

OBJS_MAN 	= ${SRCS_MAN:.c=.o}

$(NAME) : $(OBJS_MAN)
		rm -f $(NAME)
		make clean -C $(MLXDIR)
		make fclean -C $(FT_PRINTF)		
		make all -C $(MLXDIR)	
		make all -C $(FT_PRINTF)
		$(CC) $(CFLAGS) -o $(NAME) $(MLX) $^ $(FT_PRINTF)/$(PRINTF_LIB)

all : $(OBJS_MAN)

fclean : clean
		rm -f $(NAME)
		make fclean -C $(FT_PRINTF)

clean :
		rm -f $(OBJS_MAN) 
		make clean -C $(FT_PRINTF)
		make clean -C $(MLXDIR)

re : 
	make fclean 
	make all

.PHONY : fclean clean re ft_printf libft all
