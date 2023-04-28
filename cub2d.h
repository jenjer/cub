/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:42:11 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/28 18:34:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

# define PI 3.14

typedef struct s_player2
{
	double	x;
	double	y;
	int		thickness;
	double	rotation_angle;
	double	walkspeed;
	double	turnspeed;
}	t_player2;

typedef struct s_img2
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_size;
	int		endian;
	double	scale;
	int		tile_size;
	int		win_width;
}	t_img2;

typedef struct s_map2
{
	double		scale;
	int			tile_size;
	int			map_rows;
	int			map_cols;
	int			win_width;
	int			win_height;
}	t_map2;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
	int	turn_left;
	int	turn_right;
}	t_key;

// typedef	struct s_ray2
// {
//		double	ray_range; // (PI / 3.0)
//		int		ray_count; // 121
// }

#endif