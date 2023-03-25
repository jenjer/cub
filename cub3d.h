/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:33:23 by youngski          #+#    #+#             */
/*   Updated: 2023/03/25 17:20:06 by gyopark          ###   ########.fr       */
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

typedef struct s_meta_data
{
	int		fd;
	int		height;
	int		max_width;
	int		add_height;
	char	**map;
	char	**sp_map;
}	t_meta_data;

int	map_init(t_meta_data *meta, int width_temp, char **tmp_map, int idx);
int	ft_strrncmp(char *s1, char *s2, int n);
int	free_all(t_meta_data meta);

#endif
