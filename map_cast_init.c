/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:51:09 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/27 18:36:24 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_meta_data *meta, t_map2 *info2)
{
	info2->player2 = (t_player2 *)malloc(sizeof(t_player2));
	info2->player2->x = meta->player_x;
	info2->player2->y = meta->player_y;
	info2->player2->thickness = 10;
}

void	init_mini(t_map2 *info2, t_meta_data *meta, t_img2 *img2)
{
	info2->scale = img2->scale;
	info2->tile_size = img2->tile_size;
	info2->map_rows = meta->height + 2;
	info2->map_cols = meta->max_width + 2;
	info2->win_width = info2->map_cols * info2->tile_size;
	info2->win_height = info2->map_rows * info2->tile_size;
	init_player(meta, info2);
	img2->win_width = info2->map_cols * info2->tile_size;
}

void	init_img2(t_img2 *img2)
{
	// img2->img = NULL;
	// img2->data = NULL;
	img2->bpp = 0;
	img2->line_size = 0;
	img2->endian = 0;
	img2->scale = 1;
	img2->tile_size = 80;
}

void	param_init(t_press *press)
{
	press->param->mlx = mlx_init();
	press->param->win = mlx_new_window(press->param->mlx, press->info2->win_width, \
									press->info2->win_height, "mini");
	press->img2->img = mlx_new_image(press->param->mlx, (int)press->info2->scale * \
								press->info2->win_width, (int)press->info2->scale * \
									press->info2->win_height);
}

void	map_cast_init(t_press *press)
{
	press->img2 = (t_img2 *)malloc(sizeof(t_img2));
	init_img2(press->img2);
	press->info2 = (t_map2 *)malloc(sizeof(t_map2));
	init_mini(press->info2, press->meta, press->img2);
}
