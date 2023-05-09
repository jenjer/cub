/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:42:11 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/09 17:37:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

# define PI 3.141592653589793
# define LU 101
# define LD 102
# define RU 103
# define RD 104

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
	int		tile_size;
	int		win_width;
}	t_img2;

typedef struct s_map2
{
	int		tile_size;
	int		map_rows;
	int		map_cols;
	int		win_width;
	int		win_height;
	int		mts;
	int		m_dir;
	double	scale;
}	t_map2;

typedef struct s_key
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		turn_left;
	int		turn_right;
}	t_key;

typedef struct s_dp_ray
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		found_wallhit;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
}	t_dp_ray;

typedef struct s_ray2
{
	double	ray_angle;
	double	wall_hit_x;
	double	wall_hit_y;
	double	distance;
	int		was_hit_vertical;
	int		is_ray_facingdown;
	int		is_ray_facingup;
	int		is_ray_facingright;
	int		is_ray_facingleft;
}	t_ray2;

#endif
