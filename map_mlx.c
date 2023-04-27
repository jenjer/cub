/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/27 15:39:15 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

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
	if (keycode == KEY_A)
		press->info2->player2->x -= 0.1;
	if (keycode == KEY_D)
		press->info2->player2->x += 0.1;
	if (keycode == KEY_W)
		press->info2->player2->y -= 0.1;
	if (keycode == KEY_S)
		press->info2->player2->y += 0.1;
	printf("x:y = %f:%f\n", press->info2->player2->x, press->info2->player2->y);
	if (keycode == KEY_ESC)
		exit(0);
	// mlx_destroy_image(press->param->mlx, press->img2->img);
	reset_image(press);
	render_map(press);
	draw_player(press);
	return (0);
}
