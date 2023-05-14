/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/14 21:27:47 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int fix_color(t_press *press)
{
    int color;
    double x;
    double y;
    double pre_x;
    double pre_y;
    
    color = 0;
    pre_x = press->ray2->last_pre_x;
    pre_y = press->ray2->last_pre_y;
    x = press->ray2->last_x;
    y = press->ray2->last_y;


    if (y >= x && (x + y >= 1))
    {
        color = 0xff00ff;
        // 벽 위 색깔
    }
    else if (!(y >= x) && !(x + y >= 1))
    {
        color = 0xA9D0F5; //하늘 (수평)
        // 벽 아래 색깔
    }
    else if (y >= x && !(x + y >= 1))
    {
        color = 0x81F7D8; //에메랄드 (수직)
        // 벽 좌측 색깔
    }
    else if (!(y >= x) && x + y >= 1)
    {
        color = 0x00ffff;
        // 벽 우측 색깔
    }

    return color;
}

void	render_3d_projects_walls_arr(t_press *press, int ray_num, int ray_count, t_ray_arr *ray_arr)
{
	double fov_angle = 60 * (PI / 180.0);
	double distance_project_plane = ((GAME_WIDTH / 2) / tan(fov_angle / 2));
	double corrected_distance = ray_arr->distances[ray_num] * cos(ray_arr->ray_angles[ray_num] - press->player2->rotation_angle);
	double projected_wall_height = ((press->map2->mts / corrected_distance) * distance_project_plane) / 16;
	int wallStripHeight = (int)projected_wall_height;

	int wall_top_pixel = (GAME_HEIGHT / 2) - (wallStripHeight / 2);
	wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

	int wall_bottom_pixel = (GAME_HEIGHT / 2) + (wallStripHeight / 2);
	wall_bottom_pixel = wall_bottom_pixel > GAME_HEIGHT ? GAME_HEIGHT : wall_bottom_pixel;

	int color = ray_arr->colors[ray_num];
    
    if ((ray_num != 1 && ray_num != ray_count - 1) && ((color != ray_arr->colors[ray_num - 1]) && color != ray_arr->colors[ray_num + 1]))
        color = ray_arr->colors[ray_num - 1];

	for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
		for (int x = 0; x < (GAME_WIDTH / ray_count); x++)
			if (press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == 0x111111)
				press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] = color;
}

// void	render_3d_projects_walls(t_press *press, int ray_num, int ray_count)
// {
// 	double fov_angle = 60 * (PI / 180.0);
//     double distance_project_plane = ((GAME_WIDTH / 2) / tan(fov_angle / 2));
//     double corrected_distance = press->ray2->distance * cos(press->ray2->ray_angle - press->player2->rotation_angle);
//     double projected_wall_height = ((40 / corrected_distance) * distance_project_plane) / 32;
//     // int color;
//     int wallStripHeight = (int)projected_wall_height;

//     int wall_top_pixel = (GAME_HEIGHT / 2) - (wallStripHeight / 2);
//     wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;

//     int wall_bottom_pixel = (GAME_HEIGHT / 2) + (wallStripHeight / 2);
//     wall_bottom_pixel = wall_bottom_pixel > GAME_HEIGHT ? GAME_HEIGHT : wall_bottom_pixel;

//     int color = fix_color(press);
//     // int color = press->ray2->was_hit_vertical ? 0xA9D0F5 : 0x81F7D8;
//     for (int y = wall_top_pixel; y < wall_bottom_pixel; y++)
//         for (int x = 0; x < (GAME_WIDTH / ray_count); x++)
//             if (press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == 0x111111)
//                 press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] = color;
// }
