/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/15 21:36:17 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int fix_color(t_press *press)
{
    int color;
    double x;
    double y;

    color = 0;
    x = press->ray2->last_x - (int)press->ray2->last_x;
    y = press->ray2->last_y - (int)press->ray2->last_y;

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

// int count_wall_func(t_press *press, int temp_x, int temp_y)
// {
//     double *x;
//     double *y;
//     int ret;
//     int i;

//     i = 0;
//     ret = 0;
//     x = press->ray_arr->ray_x;
//     y = press->ray_arr->ray_y;
//     while (x[i])
//     {
//         if (temp_x != (int)x[i] || temp_y != (int)y[i])
//             ret++;
//         temp_x = (int)x[i];
//         temp_y = (int)y[i];
//         i++;
//     }
//     return (ret);
// }

// int *find_width_wall_pixel_count(t_press *press, int count_wall)
// {
//     int *width_wall_pixel_count;
//     int i;
//     int count;

//     i = -1;
//     count = 0;
//     width_wall_pixel_count = (char *)malloc(sizeof(char) * count_wall);
//     while (++i < count_wall)
//         width_wall_pixel_count[i] = 0;
//     while (i < RAY_COUNT && count < count_wall)
//     {
//         if ()
//         {
//             width_wall_pixel_count[count]++;
//         }
//         if ()
//         {
//             count++;
//         }
//     }
//     return width_wall_pixel_count;
// }

// int pixel_color(t_press *press)
// {
//     //	press->meta->tex[i].texture
//     int dir;
//     int img_wid;
//     int img_hei;
//     int i;
//     int count_wall;               // 벽의 갯수
//     int *width_wall_pixel_count;  // 벽 width ->벽별로 가로 레이 갯수 -> 배열 한칸에 벽의 옆면 레이 갯수가 들어간다. -> 배열 모든 칸 합하면 레이 갯수와 같다.
//     int *height_wall_pixel_count; // 벽 height -> 레이 하나당 세로 픽셀 갯수.
//     int image_pixel;

//     count_wall = count_wall_func(press); // 벽의 갯수를 세어주는 함수
//     // width_wall_pixel_count = find_width_wall_pixel_count(press,  count_wall); // 각각의 벽별로 픽셀의 갯수를 세어주는 함수
//     // 뽑은 x, y  값은 0~1 사이로 나오기 때문에 이미 비율을 뽑은 값이다.
//     // 그로 인해 이미지 width , height 값에 x 혹은 y 를 곱한 위치의 픽셀을 뽑으면 자동으로 비율이 나온다.
//     height_wall_pixel_count = find_height_wall_pixel_count(press); // 각 벽별로 높이를 세어주는 함수
//     i = 0;
//     while (1)
//     {
//         dir = find_dir(press, i);
//         img_wid = press->meta->tex[dir].width * press->ray_arr->ray_x[i];
//         img_hei = press->meta->tex[dir].height * press->ray_arr->ray_y[i];
//         // 아래는 원본 이미지의 width 계산하는 부분
//         if (dir == 0 || dir == 1)
//             image_pixel = press->meta->tex[dir].texture[(int)img_wid];
//         else
//             image_pixel = press->meta->tex[dir].texture[(int)img_hei];
//         // 아래는 원본 이미지의 height 계산
//         // 일단은 스킵
//         while ()
//         {
//         }

//         i++;
//     }
// }

void	render_3d_projects_walls_arr(t_press *press, int ray_num, int ray_count)
{
	int color = press->ray_arr->colors[ray_num];
    
    // color = pixel_color(press);

	for (int y = press->info3->wall_top_pixel[ray_num]; y < press->info3->wall_bottom_pixel[ray_num]; y++)
		for (int x = 0; x < (GAME_WIDTH / ray_count); x++)
			if (press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == press->meta->c_color->all || \
                    press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] == press->meta->f_color->all)
				press->img2->data[GAME_WIDTH * y + (x + ray_num * (GAME_WIDTH / ray_count))] = color;
}