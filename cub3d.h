/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:33:23 by youngski          #+#    #+#             */
/*   Updated: 2023/04/29 20:12:27 by gyopark          ###   ########.fr       */
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
# include <float.h> // for double max(DBL_MAX)

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
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

typedef struct s_param
{
	void	*mlx;
	void	*win;
}	t_param;

typedef struct s_press
{
	t_param		*param;
	t_meta_data	*meta;
	t_map2		*info2;
	t_img2		*img2;
	t_key		*key2;
	t_player2	*player2;
	t_ray2		*ray2;
}	t_press;

//------------------------ functions ---------------------------// 

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
void	init_player(t_meta_data *meta, t_player2 **player2);
int		check_wall(t_press *press, double x, double y);
void	draw_ray(t_press *press);

//color
int		make_rgb_bit(t_meta_data *meta);

//hooking
int		key_press(int keycode, t_press *press);
int		update_player2(t_press *press);
int		check_wall(t_press *press, double x, double y);
// int		ft_loop(t_press *press);

//rendering
void	render_map(t_press *press);
void	fill_squares(t_img2 *img2, int x, int y, int color);
int		draw_player(t_press *press);

#endif

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
