/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:04:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/28 15:58:22 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	check_wall(t_press *press, double x, double y) // update player 함수에서 조정해야함
{
	int	ix;
	int	iy;
	
	if (x < 0 || x > press->info2->win_width || y < 0 || y > press->info2->win_height)
		return (1);
	ix = floor(x);
	iy = floor(y);
	printf("ix : %d, iy : %d\n", ix, iy);
	if (press->meta->sp_map[iy][ix] == '1')
		return (1);
	return (0);
}

// info2->player2->rotation_angle = PI / 2;
// info2->player2->walkspeed = 1;
// info2->player2->turnspeed = 4 * (PI / 180);

int	update_player2(t_press *press)
{
	double	turn_direction;
	double	walk_direction;
	double	nx;
	double	ny;
	double	move_step;

	turn_direction = 0;
	walk_direction = 0;
	if (press->key2->up == 1)
		walk_direction = -1;
	if (press->key2->down == 1)
		walk_direction = 1;
	if (press->key2->turn_left == 1)
		turn_direction = -1;
	if (press->key2->turn_right == 1)
		turn_direction = 1;
	if (press->key2->left == 1)
	{
		walk_direction = -1;
	}
	if (press->key2->right == 1)
	{
		walk_direction = 1;
	}
	press->info2->player2->rotation_angle += turn_direction * (press->info2->player2->turnspeed);
	move_step = walk_direction * (press->info2->player2->walkspeed);
	nx = press->info2->player2->x + move_step * cos(press->info2->player2->rotation_angle);
	ny = press->info2->player2->y + move_step * sin(press->info2->player2->rotation_angle);
	if (press->key2->left == 1)
	{
		nx = press->info2->player2->x + move_step * sin(press->info2->player2->rotation_angle);
		ny = press->info2->player2->y - move_step * cos(press->info2->player2->rotation_angle);
	}
	if (press->key2->right == 1)
	{
		nx = press->info2->player2->x + move_step * sin(press->info2->player2->rotation_angle);
		ny = press->info2->player2->y - move_step * cos(press->info2->player2->rotation_angle);
	}
	if (!check_wall(press, nx, ny))
	{
		press->info2->player2->x = nx;
		press->info2->player2->y = ny;
	}
	printf("nx : %f, ny : %f\n", press->info2->player2->x, press->info2->player2->y);
	return (0);
}