/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:22:39 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/16 22:20:05 by gyopark          ###   ########.fr       */
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
        color = 0xA9D0F5; // 하늘 (수평)
        // 벽 아래 색깔
    }
    else if (y >= x && !(x + y >= 1))
    {
        color = 0x81F7D8; // 에메랄드 (수직)
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

int count_wall_func(t_press *press, int temp_x, int temp_y)
{
    double *x;
    double *y;
    int ret;
    int i;

    i = 0;
    ret = 0;
    x = press->ray_arr->ray_x;
    y = press->ray_arr->ray_y;
    while (x[i])
    {
        if (temp_x != (int)x[i] || temp_y != (int)y[i])
            ret++;
        temp_x = (int)x[i];
        temp_y = (int)y[i];
        i++;
    }
    return (ret);
}

int find_position_hei(t_press *press, int top, int bottom, int y, int dir)
{
    double range;
    int position;

    if (bottom < 0)
        bottom = 0;
    if (top > GAME_HEIGHT)
        top = GAME_HEIGHT;
    range = bottom - top;
    position = (int)((press->meta->tex[dir].height) * ((y/range)));
    return (position);
}

void pixel_color(t_press *press)
{
    //	press->meta->tex[i].texture
    int dir;
    int img_wid;
    int img_hwid;
    int i;
    int flag;
    
    i = 1;
    while (i < RAY_COUNT)
    {
        dir = find_dir(press, i);
        img_wid = press->meta->tex[dir].width * (press->ray_arr->ray_x[i] - (int)press->ray_arr->ray_x[i]);
        img_hwid = press->meta->tex[dir].width * (press->ray_arr->ray_y[i] - (int)press->ray_arr->ray_y[i]);
        if (dir == 0 || dir == 1)
            flag = 1;
        else
            flag = 0;
        int position_hei;
        int hei_index = -1;
        if (press->info3->wall_top_pixel[i] < -18000)
        {
            press->info3->wall_top_pixel[i] = -18000;
        }
        if (press->info3->wall_bottom_pixel[i] > 18000)
        {
            press->info3->wall_bottom_pixel[i] = 18000;
        }        
        for (int y = press->info3->wall_top_pixel[i]; y < press->info3->wall_bottom_pixel[i]; y++)
        {
            ++hei_index;
            position_hei = find_position_hei(press, press->info3->wall_top_pixel[i], press->info3->wall_bottom_pixel[i], hei_index, dir);
            for (int x = 0; x < (GAME_WIDTH / RAY_COUNT); x++)
            {
                if ((GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT))) < 0 || (GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT))) > GAME_WIDTH * GAME_HEIGHT)
                    continue;
                if (flag == 1)
                {
                    if (press->img2->data[GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT))] == press->meta->c_color->all ||
                        press->img2->data[(GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT)))] == press->meta->f_color->all)
                        press->img2->data[(GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT)))] =
                            press->meta->tex[dir].texture[(((int)img_wid + (int)(press->meta->tex[dir].width) * position_hei))];
                }
                else
                {
                    if (press->img2->data[(GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT)))] == press->meta->c_color->all ||
                        press->img2->data[(GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT)))] == press->meta->f_color->all)
                        press->img2->data[(GAME_WIDTH * y + (x + i * (GAME_WIDTH / RAY_COUNT)))] =
                            press->meta->tex[dir].texture[(((int)img_hwid + (int)(press->meta->tex[dir].width) * position_hei))];
                }
            }
        }
        i++;
    }
}

void	render_3d_projects_walls_arr(t_press *press)
{
   pixel_color(press);
}