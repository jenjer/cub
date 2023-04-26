/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:51:09 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/26 14:14:48 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_player(t_meta_data *meta, t_mini_map *info_mini)
{
	info_mini->player2 = (t_player *)malloc(sizeof(t_player));
	info_mini->player2->x = meta->player_x;
	info_mini->player2->y = meta->player_y;
	info_mini->player2->thickness = 10;
}

void	init_mini(t_mini_map *info_mini, t_meta_data *meta, t_img_2d *imgs)
{
	info_mini->scale = imgs->scale;
	info_mini->tile_size = imgs->tile_size;
	info_mini->map_rows = meta->height + 2;
	info_mini->map_cols = meta->max_width + 2;
	info_mini->win_width = info_mini->map_cols * info_mini->tile_size;
	info_mini->win_height = info_mini->map_rows * info_mini->tile_size;
	init_player(meta, info_mini);
	imgs->win_width = info_mini->map_cols * info_mini->tile_size;
}

void	init_imgs(t_img_2d *imgs)
{
	// imgs->img = NULL;
	// imgs->data = NULL;
	imgs->bpp = 0;
	imgs->line_size = 0;
	imgs->endian = 0;
	imgs->scale = 1;
	imgs->tile_size = 20;
}

void	param_init(t_param *param, t_mini_map *info_mini, t_img_2d *imgs)
{
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, 2400, \
									1300, "mini");
	imgs->img = mlx_new_image(param->mlx, (int)info_mini->scale * \
								info_mini->win_width, (int)info_mini->scale * \
									info_mini->win_height);
}

void	map_cast_init(t_meta_data *meta, t_img_2d **imgs, \
						t_mini_map **info_mini)
{
	*imgs = (t_img_2d *)malloc(sizeof(t_img_2d));
	init_imgs(*imgs);
	*info_mini = (t_mini_map *)malloc(sizeof(t_mini_map));
	init_mini(*info_mini, meta, *imgs);
}
