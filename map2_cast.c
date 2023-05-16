/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_cast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/16 21:42:25 by gyopark          ###   ########.fr       */
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
								(int)(mts * row), press->meta->c_color->all);
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

void	draw_base(t_press *press)
{
	int	y;
	int x;

	y = 0;
	x = 0;
	for (y = 0; y < GAME_HEIGHT / 2; y++)
		for (x = 0; x < GAME_WIDTH; x++)
			press->img2->data[GAME_WIDTH * y + x] = press->meta->c_color->all;
	y = GAME_HEIGHT / 2;
	x = 0;
	for (y = GAME_HEIGHT / 2; y < GAME_HEIGHT; y++)
		for (x = 0; x < GAME_WIDTH; x++)
			press->img2->data[GAME_WIDTH * y + x] = press->meta->f_color->all;
}

static int	*load_image_malloc(t_press *press, char *path, t_img1 *img1, int i)
{
	int		col;
	int		row;
	int		*result;
	
	img1->ptr = mlx_xpm_file_to_image(press->param->mlx, path, &(img1->img_width), &(img1->img_height));
	if (!(img1->ptr))
		ft_exit("wrong texture\n");
	press->meta->tex[i].width = img1->img_width;
	press->meta->tex[i].height = img1->img_height;
	img1->data = (int *)mlx_get_data_addr(img1->ptr, \
			&img1->bpp, &img1->line_size, &img1->endian);
	result = (int*)malloc(sizeof(int) * (img1->img_width * img1->img_height));
	row = -1;
	while (++row < img1->img_height)
	{
		col = -1;
		while (++col < img1->img_width)
		{
			result[img1->img_width * row + col] = img1->data[img1->img_width * row + col];
		}
	}
	mlx_destroy_image(press->param->mlx, img1->ptr);
	return (result);
}

void	load_texture(t_press  *press)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		press->meta->tex[i].texture = load_image_malloc(press, \
			press->meta->tex[i].tex_path, press->img1, i);
	}
}

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
	draw_base(press);
	printf("c color : %x f color : %x\n", press->meta->c_color->all, press->meta->f_color->all);
	load_texture(press);
	render_map(press);
	draw_player(press);
	draw_ray(press);
	mlx_hook(press->param->win, X_EVENT_KEY_PRESS, 1L << 0, key_press, press);
	mlx_loop(press->param->mlx);
	return (0);
}
