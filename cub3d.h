/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:33:23 by youngski          #+#    #+#             */
/*   Updated: 2023/03/28 20:18:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

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
}	t_color;

typedef struct s_meta_data
{
	t_color	*f_color;
	t_color	*c_color;
	int		fd;
	int		height;
	int		max_width;
	int		add_height;
	char	**map;
	char	**sp_map;
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_meta_data;

//init function
int		map_init(t_meta_data *meta, char **tmp_map, int idx);
int		map_direction_init(t_meta_data *meta);

//parsing function
int		add_color(t_meta_data *meta, char *tmp, int flag);
int		map_valid_check(t_meta_data meta);

//freeing function
int		map_free_all(t_meta_data meta);
void	free_spl(char **temp);

// utils
int		ft_isnum(char *str);
void	skip_space(char **str);
int		ft_strrncmp(char *s1, char *s2, int n);

#endif