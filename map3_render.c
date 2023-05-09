/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/09 20:48:26 by gyopark          ###   ########.fr       */
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
	distance_project_plane = ((GAME_WIDTH / 2) / tan(fov_angle / 2)) / 4;
	projected_wall_height = ((40 / press->ray2->distance) * distance_project_plane) / 4;
	wall_strip_height = (int)projected_wall_height;
	wall_top_pixel = (GAME_HEIGHT / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (GAME_HEIGHT / 2) + (wall_strip_height / 2);
	if (wall_bottom_pixel > GAME_HEIGHT)
		wall_bottom_pixel = GAME_HEIGHT;
	if (press->ray2->was_hit_vertical)
		color = 0x2EFE9A; //연두
	else
		color = 0x819FF7; //파랑
	for (int i = wall_top_pixel; i < wall_bottom_pixel; i++)
	{
		for (int j = 0; j < distance_project_plane; j++)
			if (press->img2->data[GAME_WIDTH * i + (j + (ray_num * (int)(200 / ray_num)))] == 0xEAD1DC)
				press->img2->data[GAME_WIDTH * i + (j + (ray_num * (int)(200 / ray_num)))] = color;
	}
}
