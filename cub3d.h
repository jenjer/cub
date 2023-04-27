/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:33:23 by youngski          #+#    #+#             */
/*   Updated: 2023/04/27 16:12:06 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "cub2d.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define BUTTON_X 17

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
	int	all;
}	t_color;

typedef struct s_meta_data
{
	t_color	*f_color;
	t_color	*c_color;
	int		fd;
	int		height;
	int		max_width;
	int		add_height;
	int		player_x;
	int		player_y;
	char	**map;
	char	**sp_map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		pos1_r;
	int		pos1_c;
	int		num1;
	int		**visited;
}	t_meta_data;

// after parse
// typedef struct s_img
// {
// 	void	*img;		//	pointer to the image data
// 	void	*data;		//	pointer to the first pixel of image
// 	int		size_l;		//	size of a line in bytes
// 	int		bpp;		//	number of bits per pixel
// 	int		endian;		//	endian of image data
// 	int		img_width;	//	width of the image in pixel
// 	int		img_height;	//	height of the image in pixel
// }	t_img;

typedef struct s_param
{
	void	*mlx;
	void	*win;
	//	define cast options
	// int		win_width;
	// int		win_height;
	// double	posX;
	// double	posY;
	// double	dirX;
	// double	dirY;
	// double	planeX;
	// double	planeY;
	// int		**texture;
	// t_img	img;
	// int	buf[height][width]
	// int		**texture;	// stores texture datas, two-dimensional integar array
	// double	moveSpeed;	// player movement speed
	// double	rotSpeed;	// player rotation speed
	// int		re_buf;	//	An integer that determines whether or not the game should redraw the screen.
}	t_param;

typedef struct s_press
{
	t_param		*param;
	t_meta_data	*meta;
	t_map2		*info2;
	t_img2		*img2;
}	t_press;

// -------------------------------------------- functions ---------------------------------------- // 

// init function
int		map_init(t_meta_data *meta, char **tmp_map, int idx);
int		map_direction_init(t_meta_data *meta);

// parsing function
int		add_color(t_meta_data *meta, char *tmp, int flag);
int		map_valid_check(t_meta_data *meta);

// freeing function
int		map_free_all(t_meta_data meta, t_param *param);
void	free_spl(char **temp);

// utils
int		ft_isnum(char *str);
void	skip_space(char **str);
int		ft_strrncmp(char *s1, char *s2, int n);
int		ft_exit(char *str);

// casting
int		map_cast(t_param *param, t_meta_data *meta);
void	map_cast_init(t_press *press);
void	param_init(t_press *press);
void	init_player(t_meta_data *meta, t_map2 *info2);
// void	load_image(t_param *param, int *texture, char *path, t_img *img);

//color
int		make_rgb_bit(t_meta_data *meta);

//hooking
int		key_press(int keycode, t_press *press);
// int		ft_loop(t_press *press);
// void	hooking_func(t_param *param, t_meta_data *meta, t_map2 *info2, t_img2 *img2);

//rendering
void	render_map(t_press *press);
void	fill_squares(t_img2 *img2, int x, int y, int color);
int		draw_player(t_press *press);

#endif
