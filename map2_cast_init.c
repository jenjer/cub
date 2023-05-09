/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_cast_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:51:09 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/09 19:46:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_meta_data *meta, t_player2 **player2)
{
	(*player2) = (t_player2 *)malloc(sizeof(t_player2));
	(*player2)->x = meta->player_x;
	(*player2)->y = meta->player_y;
	(*player2)->thickness = 5;
	(*player2)->rotation_angle = PI / 2;
	(*player2)->walkspeed = 0.2;
	(*player2)->turnspeed = 4 * (PI / 180);
}

void	init_map2(t_map2 *map2, t_meta_data *meta, t_img2 *img2)
{
	map2->tile_size = img2->tile_size;
	map2->mts = 0;
	map2->map_rows = meta->height + 2;
	map2->map_cols = meta->max_width + 2;
	map2->win_width = map2->map_cols * map2->tile_size;
	map2->win_height = map2->map_rows * map2->tile_size;
	map2->m_dir = LU;
	map2->scale = 0.5;
	img2->win_width = map2->map_cols * map2->tile_size;
}

void	init_img2(t_img2 *img2)
{
	img2->bpp = 0;
	img2->line_size = 0;
	img2->endian = 0;
	img2->tile_size = 14;
}

void	init_key2(t_key *key2)
{
	key2->up = 0;
	key2->down = 0;
	key2->left = 0;
	key2->right = 0;
	key2->turn_left = 0;
	key2->turn_right = 0;
}

void	map_cast_init(t_press *press)
{
	press->img2 = (t_img2 *)malloc(sizeof(t_img2));
	init_img2(press->img2);
	press->map2 = (t_map2 *)malloc(sizeof(t_map2));
	init_map2(press->map2, press->meta, press->img2);
	press->key2 = (t_key *)malloc(sizeof(t_key));
	init_key2(press->key2);
	press->player2 = (t_player2 *)malloc(sizeof(t_player2));
	init_player(press->meta, &(press->player2));
	press->ray2 = (t_ray2 *)malloc(sizeof(t_ray2));
}
