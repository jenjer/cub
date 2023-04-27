/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:04:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/27 22:42:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	check_wall(t_press *press) // update player 함수에서 조정해야함
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

int	update_player2(t_press *press)
{
	double	turn_direction;
	double	walk_direction;
	double	nx;
	double	ny;
	int		move_step;

	turn_direction = 0;
	walk_direction = 0;
	if (press->key2->left == 1)
		turn_direction = -1;
	if (press->key2->right == 1)
		turn_direction = 1;
	if (press->key2->up == 1)
		walk_direction = 1;
	if (press->key2->down == 1)
		walk_direction = -1;
		
	press->info2->player2->rotation_angle += turn_direction * (press->info2->player2->turnspeed);
	move_step = walk_direction * (press->info2->player2->walkspeed);
	nx = press->info2->player2->x + move_step * cos(press->info2->player2->rotation_angle);
	ny = press->info2->player2->y + move_step * sin(press->info2->player2->rotation_angle);
	// if (!check_wall(press))
	{
		press->info2->player2->x = nx;
		press->info2->player2->y = ny;
	}
	printf("x : %f, y : %f\n", press->info2->player2->x, press->info2->player2->y);
	return (0);
}