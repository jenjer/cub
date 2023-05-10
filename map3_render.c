/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/10 19:26:50 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_3d_projects_walls(t_press *press, int ray_num)
{
	double fov_angle = 60 * (PI / 180.0);
    double distance_project_plane = ((GAME_WIDTH / 2) / tan(fov_angle / 2));
    double corrected_distance = press->ray2->distance * cos(press->ray2->ray_angle - press->player2->rotation_angle);
    double projected_wall_height = ((40 / corrected_distance) * distance_project_plane) / 16;

    int wallStripHeight = (int)projected_wall_height;

    int wall_top_pixel = (GAME_HEIGHT / 2) - (wallStripHeight / 2);
    wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

    int wall_bottom_pixel = (GAME_HEIGHT / 2) + (wallStripHeight / 2);
    wall_bottom_pixel = wall_bottom_pixel > GAME_HEIGHT ? GAME_HEIGHT : wall_bottom_pixel;

    int color = press->ray2->was_hit_vertical ? 0xFFFFFF : 0xAAAAAA;
    for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
        for (int x = 0; x < (GAME_WIDTH / 120); x++)
            if (press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / 120))] == 0x111111)
                press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / 120))] = color;
}
