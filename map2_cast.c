/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/14 21:03:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_squares(t_press *press, int x, int y, int color)
{
	int	i;
	int	j;
	int	mts;

	mts = press->map2->mts;
	j = 0;
	while (j < mts)
	{
		i = 0;
		while (i < mts)
		{
			press->img2->data[(int)(GAME_WIDTH * (y + j)) + (x + i)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_press *press)
{
	int	col;
	int	row;
	int	mts;

	if (ft_compare(press->map2->map_rows, press->map2->map_cols))
		press->map2->mts = 400 / press->map2->map_rows;
	else
		press->map2->mts = 600 / press->map2->map_cols;
	mts = press->map2->mts;
	row = 0;
	while (row < press->map2->map_rows)
	{
		col = 0;
		while (col < press->map2->map_cols)
		{
			if (press->meta->sp_map[row][col] == '1')
				fill_squares(press, (int)(mts * col), \
								(int)(mts * row), 0x848484);
			else if (press->meta->sp_map[row][col] == 'X')
				fill_squares(press, (int)(mts * col), \
								(int)(mts * row), 0x111111);
			else if (press->meta->sp_map[row][col] == '0')
				fill_squares(press, (int)(mts * col), \
								(int)(mts * row), 0xffffff);
			col++;
		}
		row++;
	}
}

int	draw_player(t_press *press)
{
	int	row;
	int	col;
	int	mts;
	
	mts = press->map2->mts;
	row = 0;
	while (row <= (press->player2->thickness) / 2)
	{
		col = 0;
		while (col <= (press->player2->thickness) / 2)
		{
			press->img2->data[(int)(GAME_WIDTH * ((int)(press->player2->y * mts + row))) \
											+ ((int)(press->player2->x * mts + col))] = 0x0000FF;
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
			GAME_WIDTH, GAME_HEIGHT);
}

//0,0부터 이미지를 찍는데, 좌측 상단에 미니맵을 찍고 나머지 화면에는 분홍색으로 전부 칠하고 싶다.
//미니맵의 width는 win width고 이거는 tile_size(40) * sp_map(25)의 row(1000)다, 우리가 쓸 화면의 width는 1920이다.
//미니맵의 height는 win height고 이거는 tile_size(40) * sp_map(13)의 col(520)다, 우리가 쓸 화면의 height는 1080이다.
//win_width는 고정(값 자체는 변함), 여기다가 비율을 정해서 칠하는건 1/4비율로 칠할 수 있다. 쓰는 화면은 win_width을 씀.

int	map_cast(t_param *param_, t_meta_data *meta_)
{	
	t_press		*press;

	press = (t_press *)malloc(sizeof(t_press));
	press->param = param_;
	press->meta = meta_;
	map_cast_init(press);
	param_init(press);
	printf("win_width : %d\n", press->map2->win_width);
	press->img2->data = (int *)mlx_get_data_addr(press->img2->img, \
		&(press->img2->bpp), &(press->img2->line_size), \
			&((press->img2->endian)));
	
	for (int y = 0; y < GAME_HEIGHT; y++)
		for (int x = 0; x < GAME_WIDTH; x++)
			press->img2->data[GAME_WIDTH * y + x] = 0x111111;
	render_map(press);
	draw_player(press);
	draw_ray(press);
	mlx_hook(press->param->win, X_EVENT_KEY_PRESS, 1L << 0, key_press, press);
	mlx_loop(press->param->mlx);
	return (0);
}
