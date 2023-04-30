/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_press.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/30 17:54:54 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>

void	erase_key(t_press *press)
{
	press->key2->up = 0;
	press->key2->down = 0;
	press->key2->left = 0;
	press->key2->right = 0;
	press->key2->turn_left = 0;
	press->key2->turn_right = 0;
}

void	reset_image(t_press *press)
{
	mlx_destroy_image(press->param->mlx, press->img2->img);
	press->img2->img = mlx_new_image(press->param->mlx, \
				(int)(press->info2->scale) * press->info2->win_width, \
					(int)(press->info2->scale) * \
			press->info2->win_height);
	press->img2->data = (int *)mlx_get_data_addr(press->img2->img, \
						&(press->img2->bpp), &(press->img2->line_size), \
							&(press->img2->endian));
	mlx_clear_window(press->param->mlx, press->param->win);
}

void	my_ray(t_press *press)
{
	double nx;
	double	ny;
	int	i;

	i = 0;
	nx = press->player2->x;
	ny = press->player2->y;
	while (!check_wall(press, nx, ny))
	{
		
		press->img2->data[(int)((press->img2->win_width) * (ny) * press->info2->tile_size +  /*press->map2->win_height **/ (nx) * press->info2->tile_size)] = 0x000000;
		nx += -1;
	}
	mlx_put_image_to_window(press->param->mlx, press->param->win, press->img2->img, \
							0, 0);
}

/*
press->img2->data[(int)((press->info2->win_width) * (((int)(press->player2->y * (int)press->info2->tile_size) + row)) \
+ ((int)(press->player2->x * (int)press->info2->tile_size) + col))] = 0x0000FF;

*/


int	key_press(int keycode, t_press *press)
{
	if (keycode == KEY_LEFT)
		press->key2->turn_left = 1;
	if (keycode == KEY_RIGHT)
		press->key2->turn_right = 1;
	if (keycode == KEY_W)
		press->key2->up = 1;
	if (keycode == KEY_S)
		press->key2->down = 1;
	if (keycode == KEY_A)
		press->key2->left = 1;
	if (keycode == KEY_D)
		press->key2->right = 1;
	printf("up : %d, down : %d, turn_left : %d, turn_right : %d, left : %d, right : %d\n", press->key2->up, press->key2->down, \
				press->key2->turn_left, press->key2->turn_right, press->key2->left, press->key2->right);
	if (keycode == KEY_ESC)
		exit(0);
	update_player2(press);
	reset_image(press);
	render_map(press);
	draw_player(press);
//	draw_ray(press);
	my_ray(press);
	erase_key(press);
	return (0);
}
