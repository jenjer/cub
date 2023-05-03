/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/03 20:34:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h> //delete

void	fill_squares(t_img2 *img2, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(img2->tile_size))
	{
		i = 0;
		while (i < (int)(img2->tile_size))
		{
			img2->data[(int)((img2->win_width) * (y + j)) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_press *press)
{
	int	col;
	int	row;

	row = 0;
	while (row < press->info2->map_rows)
	{
		col = 0;
		while (col < press->info2->map_cols)
		{
			if (press->meta->sp_map[row][col] == '1')
				fill_squares(press->img2, (int)(press->info2->tile_size * col), \
								(int)(press->info2->tile_size * row), 0x000000);
			else if (press->meta->sp_map[row][col] == 'X')
				fill_squares(press->img2, (int)(press->info2->tile_size * col), \
								(int)(press->info2->tile_size * row), 0xff00ff);
			else if (press->meta->sp_map[row][col] == '0')
				fill_squares(press->img2, (int)(press->info2->tile_size * col), \
								(int)(press->info2->tile_size * row), 0xffffff);
			col++;
		}
		row++;
	}
}

int	draw_player(t_press *press)
{
	int	row;
	int	col;

	row = 0;
	while (row <= (press->player2->thickness) / 2)
	{
		col = 0;
		while (col <= (press->player2->thickness) / 2)
		{
			press->img2->data[(int)((press->info2->win_width) * (((int)(press->player2->y * (int)press->info2->tile_size) + row)) \
											+ ((int)(press->player2->x * (int)press->info2->tile_size) + col))] = 0x0000FF;
			col++;
		}
		row++;
	}
	mlx_put_image_to_window(press->param->mlx, \
				press->param->win, press->img2->img, 0, 0);
	return (0);
}

void	param_init(t_press *press)
{
	press->param->mlx = mlx_init();
	press->param->win = mlx_new_window(press->param->mlx, \
			GAME_WIDTH, GAME_HEIGHT, "mini");
	press->img2->img = mlx_new_image(press->param->mlx, \
			(int) GAME_WIDTH, (int) GAME_HEIGHT);
	//이게 맞다
}

//0,0부터 이미지를 찍는데, 좌측 상단에 미니맵을 찍고 나머지 화면에는 분홍색으로 전부 칠하고 싶다.
//미니맵의 width는 win width고 이거는 tile_size(40) * sp_map(25)의 row(1000)다, 우리가 쓸 화면의 width는 1920이다.
//미니맵의 height는 win height고 이거는 tile_size(40) * sp_map(13)의 col(520)다, 우리가 쓸 화면의 height는 1080이다.
//win_width는 고정(값 자체는 변함), 여기다가 비율을 정해서 칠하는건 1/4비율로 칠할 수 있다. 쓰는 화면은 win_width을 씀.

int	map_cast(t_param *param_, t_meta_data *meta_)
{	
	t_press		*press;
	int	x;
	int	y;

	press = (t_press *)malloc(sizeof(t_press));
	press->param = param_;
	press->meta = meta_;
	map_cast_init(press);
	param_init(press);
	printf("win_width : %d\n", press->info2->win_width);
	press->img2->data = (int *)mlx_get_data_addr(press->img2->img, \
		&(press->img2->bpp), &(press->img2->line_size), \
			&((press->img2->endian)));
	for (y = 0; y < GAME_HEIGHT; y++)
		for (x = 0; x < GAME_WIDTH; x++)
			press->img2->data[GAME_WIDTH * y + x] = 0xEAD1DC;
	// mlx_put_image_to_window(press->param->mlx, \
	// 			press->param->win, press->img2->img, 0, 0);

	render_map(press);
	draw_player(press);
	mlx_hook(press->param->win, X_EVENT_KEY_PRESS, 1L << 0, key_press, press);
	mlx_loop(press->param->mlx);
	return (0);
}
