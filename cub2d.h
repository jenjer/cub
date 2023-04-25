/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub2d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 18:42:11 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/25 16:30:13 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB2D_H
# define CUB2D_H

typedef struct s_player2
{
	int	x;
	int	y;
	int	thickness;
}	t_player;

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
}	t_img_2d;
typedef struct s_mini_map
{
	double		scale;
	int			tile_size;
	int			map_rows;
	int			map_cols;
	int			win_width;
	int			win_height;
	t_player	*player2;
}	t_mini_map;

#endif