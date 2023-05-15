/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/15 18:43:41 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int fix_color(t_press *press)
{
    int color;
    double x;
    double y;

    color = 0;
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

int find_dir(t_press *press, int i)
{
    int color;
    color = press->ray_arr->colors[i];
    if (color == 0xff00ff)
        return 0;
    if (color == 0xA9D0F5)
        return 1;
    if (color == 0x81F7D8)
        return 2;
    if (color == 0x00ffff)
        return 3;
    return (-1);
}

// int pixel_color(t_press *press)
// {
//     //	press->meta->tex[i].texture
//     int dir;
//     int img_wid;
//     int img_hei;
//     int i;
//     int count_wall; // 벽의 갯수
//     int *width_wall_pixel_count;//벽 width ->벽별로 가로 레이 갯수 -> 배열 한칸에 벽의 옆면 레이 갯수가 들어간다. -> 배열 모든 칸 합하면 레이 갯수와 같다.
//     int *height_wall_pixel_count;//벽 height -> 레이 하나당 세로 픽셀 갯수.
//     count_wall = find_count_wall(press); //벽의 갯수를 세어주는 함수
//     width_wall_pixel_count = find_width_wall_pixel_count(press,  count_wall); // 각각의 벽별로 픽셀의 갯수를 세어주는 함수
//     height_wall_pixel_count = find_height_wall_pixel_count(press); // 각 벽별로 높이를 세어주는 함수
//     i = 0;
//     while (1)
//     {
//         dir = find_dir(press, i);
//         img_wid = press->meta->tex[dir].width;
//         img_hei = press->meta->tex[dir].height;
//         // 아래는 원본 이미지와 벽 이미지의 비율 계산
        
//         i++;
//     }


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
			if (press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == press->meta->c_color->all || \
                    press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == press->meta->f_color->all)
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
