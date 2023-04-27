/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/27 18:42:20 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h> //delete

void	fill_squares(t_img2 *img2, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(img2->scale * img2->tile_size))
	{
		i = 0;
		while (i < (int)(img2->scale * img2->tile_size))
		{
			img2->data[(int)(img2->scale * (img2->win_width)) * (y + j) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_press *press)
{
	int	col;
	int	row;
	// img2->data = (int *)mlx_get_data_addr(img2->img, \
	// 				&(img2->bpp), &(img2->line_size), &(img2->endian));
	row = 0;
	while (row < press->info2->map_rows)
	{
		col = 0;
		while (col < press->info2->map_cols)
		{
			if (press->meta->sp_map[row][col] == '1')
				fill_squares(press->img2, (int)(press->info2->scale * press->info2->tile_size * col), \
								(int)(press->info2->scale * press->info2->tile_size * row), 0x000000);
			else if (press->meta->sp_map[row][col] == 'X')
				fill_squares(press->img2, (int)(press->info2->scale * press->info2->tile_size * col), \
								(int)(press->info2->scale * press->info2->tile_size * row), 0xff00ff);			
			else if (press->meta->sp_map[row][col] == '0')
				fill_squares(press->img2, (int)(press->info2->scale * press->info2->tile_size * col), \
								(int)(press->info2->scale * press->info2->tile_size * row), 0xffffff);
			col++;
		}
		row++;
	}
	//mlx_put_image_to_window(param->mlx, param->win, img2->img, 0, 0);
}

int	draw_player(t_press *press)
{
	int	row;
	int col;

	// row = -(press->info2->player2->thickness) / 2;
	// 음수로 하면 삐져나옴
	row = 0;
	while (row <= (press->info2->player2->thickness) / 2)
	{
		// col = -(press->info2->player2->thickness) / 2;
		// 같이 바꿔서 비율 맞춰줌
		col = 0;
		while (col <= (press->info2->player2->thickness) / 2)
		{
			press->img2->data[(int)((press->info2->win_width) * (((int)(press->info2->player2->y * (int)press->info2->tile_size) + row)) \
											+ ((int)(press->info2->player2->x * (int)press->info2->tile_size) + col))] = 0x0000FF;
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(press->param->mlx, press->param->win, press->img2->img, \
							0, 0);
	return (0);
}

int	map_cast(t_param *param_, t_meta_data *meta_)
{	
	t_press		*press;

	press = (t_press *)malloc(sizeof(t_press));
	press->param = param_;
	press->meta = meta_;
	map_cast_init(press);
	param_init(press);
	press->img2->data = (int *)mlx_get_data_addr(press->img2->img, \
					&(press->img2->bpp), &(press->img2->line_size), &((press->img2->endian)));
	render_map(press);
	draw_player(press);
	// hooking_func(param, meta, press->info2, img2);
	mlx_hook(press->param->win, X_EVENT_KEY_PRESS, 1L<<0, key_press, press);
	mlx_loop(press->param->mlx);
	return (0);
}
