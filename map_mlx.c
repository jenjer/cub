/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/27 18:53:34 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

int	check_wall(t_press *press)
{
	double	ny;
	double	nx;
	double	nny;

	ny = floor(press->info2->player2->y);
	nx = floor(press->info2->player2->x);
	nny = (press->info2->player2->y + 0.05);
	if (press->meta->sp_map[(int) ny][(int) nx] == '1' \
			|| press->meta->sp_map[(int) nny][(int) nx] == '1')
		return (1);
	return (0);
}

void	reset_image(t_press *press)
{
	mlx_destroy_image(press->param->mlx, press->img2->img);
	press->img2->img = mlx_new_image(press->param->mlx, (int)(press->info2->scale) * \
			press->info2->win_width, (int)(press->info2->scale) * \
			press->info2->win_height);
	press->img2->data = (int *)mlx_get_data_addr(press->img2->img, \
                    &(press->img2->bpp), &(press->img2->line_size), &(press->img2->endian));
	mlx_clear_window(press->param->mlx, press->param->win);
}

int	key_press(int keycode, t_press *press)
{
	double	ox;
	double	oy;

	ox = press->info2->player2->x;
	oy = press->info2->player2->y;
	if (keycode == KEY_A)
	{
		press->info2->player2->x -= 0.05;
		if (check_wall(press))
			press->info2->player2->x = ox;
	}
	if (keycode == KEY_D)
	{
		press->info2->player2->x += 0.05;
		if (check_wall(press))
			press->info2->player2->x = ox;
	}
	if (keycode == KEY_W)
	{
		press->info2->player2->y -= 0.05;
		if (check_wall(press))
			press->info2->player2->y = oy;
	}
	if (keycode == KEY_S)
	{
		press->info2->player2->y += 0.05;
		if (check_wall(press))
			press->info2->player2->y = oy;
	}
	if (keycode == KEY_ESC)
		exit(0);
	reset_image(press);
	render_map(press);
	draw_player(press);
	return (0);
}
