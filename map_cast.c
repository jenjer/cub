/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/24 20:59:29 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub2d.h"

void	init_mini(t_mini_map *info_mini, t_meta_data *meta, t_img_2d *imgs)
{
	info_mini->scale = imgs->scale;
	info_mini->tile_size = imgs->tile_size;
	info_mini->map_rows = meta->height;
	info_mini->map_cols = meta->max_width;
	info_mini->win_width = info_mini->map_cols * info_mini->tile_size;
	info_mini->win_height = info_mini->map_rows * info_mini->tile_size;
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
	imgs->tile_size = 80;
}

void	param_init(t_param *param, t_mini_map *info_mini, t_img_2d *imgs)
{
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, info_mini->win_width, \
									info_mini->win_height, "mini");
	imgs->img = mlx_new_image(param->mlx, (int)info_mini->scale * \
								info_mini->win_width, (int)info_mini->scale * \
									info_mini->win_height);
}

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

	imgs->data = (int *)mlx_get_data_addr(imgs->img, \
					&(imgs->bpp), &(imgs->line_size), &(imgs->endian));
	row = 0;
	while (row < info_mini->map_rows)
	{
		col = 0;
		while (col < info_mini->map_cols)
		{
			if (meta->sp_map[row][col] == '1')
				fill_squares(imgs, (int)(info_mini->scale * info_mini->tile_size * col), \
								(int)(info_mini->scale * info_mini->tile_size * row), 0xffffff);
			else
				fill_squares(imgs, (int)(info_mini->scale * info_mini->tile_size * col), \
								(int)(info_mini->scale * info_mini->tile_size * row), 0x000000);
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(param->mlx, param->win, imgs->img, \
			(int)(info_mini->win_width * (info_mini->scale)), \
				(int)(info_mini->win_height * (info_mini->scale)));
}

int	map_cast(t_param *param, t_meta_data *meta)
{	
	t_img_2d		*imgs;
	t_mini_map		*info_mini;

	imgs = (t_img_2d *)malloc(sizeof(t_img_2d));
	init_imgs(imgs);
	info_mini = (t_mini_map *)malloc(sizeof(t_mini_map));
	init_mini(info_mini, meta, imgs);
	param_init(param, info_mini, imgs);
	render_map(param, info_mini, imgs, meta);
	mlx_loop(param->mlx);
	return (0);
}
