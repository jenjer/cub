/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/03 17:15:43 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d_projects_walls(t_press *press, int ray_num)
{
	double	fov_angle;
	double	distance_project_plane;
	double	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		color;

	fov_angle = 60 * (PI / 180);
	distance_project_plane = (GAME_WIDTH / 2) / tan(fov_angle / 2);
	projected_wall_height = (press->info2->tile_size / press->ray2->distance) * distance_project_plane;
	wall_strip_height = (int)projected_wall_height;
	wall_top_pixel = (press->info2->win_height / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (press->info2->win_height / 2) + (wall_strip_height);
	if (wall_bottom_pixel > press->info2->win_height)
		wall_bottom_pixel = press->info2->win_height;
	if (press->ray2->was_hit_vertical)
		color = 0xffffff;
	else
		color = 0xaaaaaa;
	for (int i = wall_top_pixel; i < wall_bottom_pixel; i++)
	{
		for (int j = 0; j < GAME_WIDTH; j++)
			press->img2->data[GAME_WIDTH * j + (i + ray_num * GAME_WIDTH)] = color;
	}
}