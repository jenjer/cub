/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/26 17:51:21 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




#include <stdio.h> //delete

void	fill_squares(t_img_2d *imgs, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(imgs->scale * imgs->tile_size))
	{
		i = 0;
		while (i < (int)(imgs->scale * imgs->tile_size))
		{
			imgs->data[(int)(imgs->scale * (imgs->win_width)) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_param *param, t_mini_map *info_mini, t_img_2d *imgs, \
						t_meta_data *meta)
{
	int	col;
	int	row;

	(void) param;
	// imgs->data = (int *)mlx_get_data_addr(imgs->img, \
	// 				&(imgs->bpp), &(imgs->line_size), &(imgs->endian));
	row = 0;
	while (row < info_mini->map_rows)
	{
		col = 0;
		while (col < info_mini->map_cols)
		{
			if (meta->sp_map[row][col] == '1')
				fill_squares(imgs, (int)(info_mini->scale * info_mini->tile_size * col), \
								(int)(info_mini->scale * info_mini->tile_size * row), 0x000000);
			else if (meta->sp_map[row][col] == 'X')
				fill_squares(imgs, (int)(info_mini->scale * info_mini->tile_size * col), \
								(int)(info_mini->scale * info_mini->tile_size * row), 0xff00ff);			
			else
				fill_squares(imgs, (int)(info_mini->scale * info_mini->tile_size * col), \
								(int)(info_mini->scale * info_mini->tile_size * row), 0xffffff);
			col++;
		}
		row++;
	}
	//mlx_put_image_to_window(param->mlx, param->win, imgs->img, 0, 0);
}

int	draw_player(t_param *param, t_mini_map *info_mini, t_img_2d *imgs)
{
	int row;
	int col;
	
	// row = -(info_mini->player2->thickness) / 2;
	// 음수로 하면 삐져나옴
	row = 0;
	while (row <= (info_mini->player2->thickness) / 2)
	{
		// col = -(info_mini->player2->thickness) / 2;
		// 같이 바꿔서 비율 맞춰줌
		col = 0;
		while (col <= (info_mini->player2->thickness) / 2)
		{
			imgs->data[(int)((info_mini->win_width) * ((info_mini->player2->y * info_mini->tile_size) + row) \
											+ ((info_mini->player2->x * info_mini->tile_size) + col))] = 0x0000FF;
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(param->mlx, param->win, imgs->img, \
							0, 0);
	printf("working\n");
	return (0);
}

int	map_cast(t_param *param, t_meta_data *meta)
{	
	t_img_2d		*imgs;
	t_mini_map		*info_mini;

	map_cast_init(meta, &imgs, &info_mini);
	param_init(param, info_mini, imgs);
	imgs->data = (int *)mlx_get_data_addr(imgs->img, \
					&(imgs->bpp), &(imgs->line_size), &(imgs->endian));
	render_map(param, info_mini, imgs, meta);
	draw_player(param, info_mini, imgs);
	hooking_func(param, meta, info_mini, imgs);
	mlx_loop(param->mlx);
	return (0);
}
