/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 22:04:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/17 18:23:45 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/cub3d.h"

int	check_wall(t_press *press, double x, double y)
{
	int	ix;
	int	iy;
	int	tx;
	int	ty;

	if (x < 0 || x > press->map2->map_cols || y < 0 || y > press->map2->map_rows)
		return (1);
	ix = floor(x + 0.1);
	iy = floor(y + 0.1);
	tx = floor(x - 0.1);
	ty = floor(y - 0.1);
	if (press->meta->sp_map[(int)floor(y)][(int)floor(x)] == '1' || press->meta->sp_map[(int)floor(y)][(int)floor(x)] == 'X' ||
			press->meta->sp_map[iy][ix] == '1' || press->meta->sp_map[iy][ix] == 'X' || \
				press->meta->sp_map[ty][tx] == '1' || press->meta->sp_map[ty][tx] == 'X')
		return (1);
	return (0);
}

// map2->player2->rotation_angle = PI / 2; 거의 90도 1.57
// map2->player2->turnspeed = 4 * (PI / 180); 거의 4도

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
		walk_direction = -1;
	if (press->key2->right == 1)
		walk_direction = 1;
	press->player2->rotation_angle += turn_direction * (press->player2->turnspeed);
	move_step = walk_direction * (press->player2->walkspeed);
	nx = press->player2->x + move_step * cos(press->player2->rotation_angle);
	ny = press->player2->y + move_step * sin(press->player2->rotation_angle);
	if (press->key2->left == 1)
	{
		nx = press->player2->x + move_step * sin(press->player2->rotation_angle);
		ny = press->player2->y - move_step * cos(press->player2->rotation_angle);
	}
	if (press->key2->right == 1)
	{
		nx = press->player2->x + move_step * sin(press->player2->rotation_angle);
		ny = press->player2->y - move_step * cos(press->player2->rotation_angle);
	}
	if (!check_wall(press, nx, ny))
    {
        press->player2->x = nx;
        press->player2->y = ny;
    }
    else
    {
        double slide_step = move_step;
        double slide_x = press->player2->x + slide_step * cos(press->player2->rotation_angle);
        double slide_y = press->player2->y + slide_step * sin(press->player2->rotation_angle);

        if (!check_wall(press, slide_x, press->player2->y))
            press->player2->x = slide_x;
        if (!check_wall(press, press->player2->x, slide_y))
            press->player2->y = slide_y;
    }
	return (0);
}
