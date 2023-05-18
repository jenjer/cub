/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/18 17:11:33 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	fix_color(t_press *press)
{
	int		color;
	double	x;
	double	y;

	color = 0;
	x = press->ray2->last_x - (int)press->ray2->last_x;
	y = press->ray2->last_y - (int)press->ray2->last_y;
	if (y >= x && (x + y >= 1))
		color = 0xff00ff;
	else if (!(y >= x) && !(x + y >= 1))
		color = 0xA9D0F5;
	else if (y >= x && !(x + y >= 1))
		color = 0x81F7D8;
	else if (!(y >= x) && x + y >= 1)
		color = 0x00ffff;
	return (color);
}

void	find_dir(t_press *press, int i)
{
	int	color;

	color = press->ray_arr->colors[i];
	if (color == 0xff00ff)
		press->info3->dir = 0;
	if (color == 0xA9D0F5)
		press->info3->dir = 1;
	if (color == 0x81F7D8)
		press->info3->dir = 2;
	if (color == 0x00ffff)
		press->info3->dir = 3;
}

int	count_wall_func(t_press *press, int temp_x, int temp_y)
{
	double	*x;
	double	*y;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	x = press->ray_arr->ray_x;
	y = press->ray_arr->ray_y;
	while (x[i])
	{
		if (temp_x != (int)x[i] || temp_y != (int)y[i])
			ret++;
		temp_x = (int)x[i];
		temp_y = (int)y[i];
		i++;
	}
	return (ret);
}

int	find_position_hei(t_press *press, int i, int y, int dir)
{
	double	range;
	int		position;
	int		top;
	int		bot;

	top = press->info3->wall_top_pixel[i];
	bot = press->info3->wall_bot_pixel[i];
	if (bot < 0)
		bot = 0;
	if (top > GAME_HEIGHT)
		top = GAME_HEIGHT;
	range = bot - top;
	position = (int)((press->meta->tex[dir].height) * ((y / range)));
	return (position);
}

void	find_wid(t_press *press, int *flag, int num)
{
	if (press->info3->dir == 0 || press->info3->dir == 1)
	{
		*flag = 1;
		press->info3->img_wid = press->meta->tex[press->info3->dir].width * \
				(press->ray_arr->ray_x[num] - (int)press->ray_arr->ray_x[num]);
	}
	else
	{
		*flag = 0;
		press->info3->img_hwid = press->meta->tex[press->info3->dir].width * \
				(press->ray_arr->ray_y[num] - (int)press->ray_arr->ray_y[num]);
	}
}

void	normalize_top_bot(t_press *press, int num)
{
	if (press->info3->wall_top_pixel[num] < -9000)
		press->info3->wall_top_pixel[num] = -9000;
	if (press->info3->wall_bot_pixel[num] > 9000)
		press->info3->wall_bot_pixel[num] = 9000;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/18 16:36:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	draw_top_bot(t_press *press, int down, int hei_index)
// {
// 	while (x < (GAME_WIDTH / RAY_COUNT))
// 	{
		
// 	}	
// }

void	pixel_render(t_press *press)
{
	int	idx;
	int	flag;
	int	y;
	int	x;
	int	position_hei;
	int	hei_index;

	idx = 1;
	y = 0;
	x = 0;
	position_hei = 0;
	hei_index = 0;
	while (idx < RAY_COUNT)
	{
		find_dir(press, idx);
		find_wid(press, &flag, idx);
		normalize_top_bot(press, idx);

		
		hei_index = -1;
		// y = press->info3->wall_top_pixel[idx];
		// while (y < press_info3->wall_bot_pixel[idx])
		// {
		// 	draw_top_bot(press, y, -1);
		// 	y++;
		// }

		
		for (int y = press->info3->wall_top_pixel[idx]; y < press->info3->wall_bot_pixel[idx]; y++)
		{
			++hei_index;
			position_hei = find_position_hei(press, idx, hei_index, press->info3->dir);
			for (int x = 0; x < (GAME_WIDTH / RAY_COUNT); x++)
			{
				if ((GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT))) < 0 || (GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT))) > GAME_WIDTH * GAME_HEIGHT)
				{
					// x++;
					continue;
				}
				if (flag == 1)
				{
					if (press->img2->data[GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT))] == press->meta->c_color->all ||
							press->img2->data[(GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT)))] == press->meta->f_color->all)
						press->img2->data[(GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT)))] =
							press->meta->tex[press->info3->dir].texture[(((int)press->info3->img_wid + (int)(press->meta->tex[press->info3->dir].width) * position_hei))];
				}
				else
				{
					if (press->img2->data[(GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT)))] == press->meta->c_color->all ||
							press->img2->data[(GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT)))] == press->meta->f_color->all)
						press->img2->data[(GAME_WIDTH * y + (x + idx * (GAME_WIDTH / RAY_COUNT)))] =
							press->meta->tex[press->info3->dir].texture[(((int)press->info3->img_hwid + (int)(press->meta->tex[press->info3->dir].width) * position_hei))];
				}
			}
		}
		
		idx++;
	}
}
