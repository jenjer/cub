/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:20:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/15 21:25:56 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	check_vertical(t_press *press, double rx, double ry)
// {
// 	if ((check_wall_light(press, rx - 1, ry) == 1 && check_wall_light(press, rx + 1, ry) == 1) && \
// 			(check_wall_light(press, rx, ry - 1) == 0 || check_wall_light(press, rx, ry + 1) == 0))
// 			press->ray2->was_hit_vertical = 0; //초록
// 	else if ((check_wall_light(press, rx - 1, ry) == 0 || check_wall_light(press, rx + 1, ry) == 0) && \
// 		(check_wall_light(press, rx, ry - 1) == 1 && check_wall_light(press, rx, ry + 1) == 1))
// 			press->ray2->was_hit_vertical = 1; //파랑
//	else if ((check_wall_hv(press, rx-1, ry) == 0) && (check_wall_hv(press, rx+1, ry) == 0) &&)
// }

int	check_wall_light(t_press *press, double x, double y)
{
	int	ix;
	int	iy;

	if (x < 0 || x > press->meta->max_width || y < 0 || y > press->meta->height)
		return (1);
	ix = floor(x);
	iy = floor(y);
	return (press->meta->sp_map[iy][ix] != '0');
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	draw_line(t_press *press, double x1, double y1, double x2, double y2)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_value;

	ray_x = press->player2->x;
	ray_y = press->player2->y;
	dx = (x2 - x1);
	dy = (y2 - y1);
	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!check_wall_light(press, ray_x, ray_y))
		{
			press->img2->data[(GAME_WIDTH * \
				(int)((ray_y) * (press->map2->mts))) + \
				(int)((ray_x) * (press->map2->mts))] = 0xff0000;
		}
		else
		{
			press->ray2->last_x = ray_x;
			press->ray2->last_y = ray_y;
			// printf("ray_x : %f ray_y : %f sosu_x : %f sosu_y : %f\n", ray_x, ray_y, ray_x -(int)ray_x, ray_y-(int)ray_y);
			break ;
		}
		ray_y += (dy / (press->map2->mts)) / 100;
		ray_x += (dx / (press->map2->mts)) / 100;
	}
	// check_vertical(press, ray_x, ray_y);
	press->ray2->distance = distance_between_points(x1, y1, ray_x, ray_y);
}

void	cal_distance(t_press *press, t_dp_ray *hv)
{
	if (hv->found_wallhit == 1)
	{
		hv->distance = distance_between_points(press->player2->x, \
		press->player2->y, hv->wall_hitx, hv->wall_hity);
	}
	else
		hv->distance = DBL_MAX;
}

void	cal_ray(t_press *press, t_dp_ray *hv)
{
	double	next_touch_x;
	double	next_touch_y;
	// double	check_touch_y;

	next_touch_x = hv->xintercept;
	next_touch_y = hv->yintercept;

    while (next_touch_x >= 0 && next_touch_x <= GAME_WIDTH && next_touch_y >= 0 && next_touch_y <= GAME_HEIGHT) {
        if (check_wall_light(press, next_touch_x, next_touch_y - (press->ray2->is_ray_facingdown ? 1 : 0))) {
            hv->found_wallhit = 1;
            hv->wall_hitx = next_touch_x;
            hv->wall_hity = next_touch_y;
            break;
        } else {
            next_touch_x += hv->xstep;
            next_touch_y += hv->ystep;
        }
    }
    cal_distance(press, hv);
}

void	cal_vert_ray(t_press *press, t_dp_ray *vert)
{
	vert->found_wallhit = 0;
	vert->wall_hitx = 0;
	vert->wall_hity = 0;

	vert->xintercept = floor(press->player2->x / press->map2->mts) * (press->map2->mts);
    vert->xintercept += press->ray2->is_ray_facingright ? press->map2->mts : 0;

	vert->yintercept = press->player2->y + (vert->xintercept - press->player2->x) * tan(press->ray2->ray_angle);
	
	vert->xstep = press->map2->mts;
    vert->xstep *= press->ray2->is_ray_facingleft ? -1 : 1;

	vert->ystep = press->map2->mts * tan(press->ray2->ray_angle);
    vert->ystep *= (press->ray2->is_ray_facingup && vert->ystep > 0) ? -1 : 1;
    vert->ystep *= (press->ray2->is_ray_facingdown && vert->ystep < 0) ? -1 : 1;
	cal_ray(press, vert);
}

void	cal_horz_ray(t_press *press, t_dp_ray *horz)
{
	horz->found_wallhit = 0;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(press->player2->y / press->map2->mts) * (press->map2->mts);
    horz->yintercept += press->ray2->is_ray_facingdown ? press->map2->mts : 0;

	horz->xintercept = press->player2->x + (horz->yintercept - press->player2->y) / tan(press->ray2->ray_angle);
	horz->ystep = press->map2->mts;
    horz->ystep *= press->ray2->is_ray_facingup ? -1 : 1;

	horz->xstep = press->map2->mts / tan(press->ray2->ray_angle);
    horz->xstep *= (press->ray2->is_ray_facingleft && horz->xstep > 0) ? -1 : 1;
    horz->xstep *= (press->ray2->is_ray_facingright && horz->xstep < 0) ? -1 : 1;
	cal_ray(press, horz);
}

double	normalize_angle(double angle)
{
	if (angle >= 0)
		while (angle >= 2 * PI)
			angle -= 2 * PI;
	else
		while (angle <= 0)
			angle += 2 * PI;
	return (angle);
}

void	ray_init(t_ray2 *ray2, double ray_angle)
{
	ray2->ray_angle = normalize_angle(ray_angle);
	ray2->wall_hit_x = 0;
	ray2->wall_hit_y = 0;
	ray2->distance = 0;
	ray2->was_hit_vertical = 0;

    ray2->is_ray_facingup = ray2->ray_angle > 0 && ray2->ray_angle < PI;
    ray2->is_ray_facingdown = !ray2->is_ray_facingup;
    ray2->is_ray_facingleft = ray2->ray_angle < 0.5 * PI || ray2->ray_angle > 1.5 * PI;
    ray2->is_ray_facingright = !ray2->is_ray_facingleft;
}

void	draw_one_ray(t_press *press, double angle, int ray_num, int ray_count, t_ray_arr *ray_arr)
{
	t_dp_ray	horz;
	t_dp_ray	vert;

	ray_init(press->ray2, angle);
	cal_horz_ray(press, &horz);
	cal_vert_ray(press, &vert);
	(void) ray_count;
	if (vert.distance < horz.distance)
	{
		press->ray2->wall_hit_x = vert.wall_hitx;
		press->ray2->wall_hit_y = vert.wall_hity;
		press->ray2->distance = vert.distance;
		// press->ray2->was_hit_vertical = 1;
	}
	else
	{
		press->ray2->wall_hit_x = horz.wall_hitx;
		press->ray2->wall_hit_y = horz.wall_hity;
		press->ray2->distance = horz.distance;
		// press->ray2->was_hit_vertical = 0;
	}
	draw_line(press, press->player2->x, press->player2->y,
		press->ray2->wall_hit_x, press->ray2->wall_hit_y);
	ray_arr->distances[ray_num] = press->ray2->distance;
	ray_arr->ray_angles[ray_num] = press->ray2->ray_angle;
	ray_arr->colors[ray_num] = fix_color(press);
	ray_arr->ray_x[ray_num] = press->ray2->last_x;
	ray_arr->ray_y[ray_num] = press->ray2->last_y; 
	// render_3d_projects_walls(press, ray_num, ray_count);
}

void	ray_arr_init(t_ray_arr *ray_arr, int ray_count)
{
	ray_arr->ray_angles = (double *)malloc(sizeof(double) * ray_count);
	memset(ray_arr->ray_angles, 0, sizeof(double) * ray_count);
	ray_arr->distances = (double *)malloc(sizeof(double) * ray_count);
	memset(ray_arr->distances, 0, sizeof(double) * ray_count);
	ray_arr->ray_x = (double *)malloc(sizeof(double) * ray_count);
	memset(ray_arr->distances, 0, sizeof(double) * ray_count);
	ray_arr->ray_y = (double *)malloc(sizeof(double) * ray_count);
	memset(ray_arr->distances, 0, sizeof(double) * ray_count);
	ray_arr->colors = (int *)malloc(sizeof(int) * ray_count);
	memset(ray_arr->colors, 0, ray_count);
}

void	info3_init(t_press *press, int ray_num)
{
	t_3d	*info3;
	double	corrected_distance;
	double	projected_wall_height;
	double	wall_strip_height;

	info3 = (t_3d *)malloc(sizeof(t_3d));
	memset(info3, 0, sizeof(t_3d));
	info3->wall_top_pixel = (int *) malloc(sizeof(int) * RAY_COUNT);
	info3->wall_bottom_pixel = (int *) malloc(sizeof(int) * RAY_COUNT);
	info3->fov_angle = 60 * (PI / 180.0);
	info3->distance_project_plane = ((GAME_WIDTH / 2) / tan(info3->fov_angle / 2));
	while (ray_num < RAY_COUNT)
	{
		corrected_distance = press->ray_arr->distances[ray_num] * \
				cos(press->ray_arr->ray_angles[ray_num] - press->player2->rotation_angle);
		projected_wall_height = ((press->map2->mts / corrected_distance) * (info3->distance_project_plane)) / 16;
		wall_strip_height = projected_wall_height;
		info3->wall_top_pixel[ray_num] = (GAME_HEIGHT / 2) - (wall_strip_height / 2);
		info3->wall_top_pixel[ray_num] = info3->wall_top_pixel[ray_num] < 0 ? 0 : info3->wall_top_pixel[ray_num];
		info3->wall_bottom_pixel[ray_num] = (GAME_HEIGHT / 2) + (wall_strip_height / 2);
		info3->wall_bottom_pixel[ray_num] = info3->wall_bottom_pixel[ray_num] > GAME_HEIGHT ? GAME_HEIGHT : info3->wall_bottom_pixel[ray_num];
		ray_num++;
	}
	press->info3 = info3;
}

void draw_ray(t_press *press)
{
	double		angle;
	double		ray_range;
	int			ray_count;
	int			i;
	t_ray_arr	*ray_arr_;

	i = 1;
	ray_range = PI / 3.0; // 60도 (플레이어의 시야각)
	ray_count = 400;
	angle = press->player2->rotation_angle; // 플레이어가 바라보는 각도
	ray_arr_ = (t_ray_arr*) malloc(sizeof(t_ray_arr));
	ray_arr_init(ray_arr_, ray_count);
	// 시야각이 60라면, 플레이어의 최대 각도는 +30도가 된다.
	press->ray_arr = ray_arr_;
	while (i < ray_count)
	{
		draw_one_ray(press, angle - (ray_range / 2.0), i, ray_count, press->ray_arr);
		angle += ray_range / ray_count;
		i++;
	}
	info3_init(press, 1);
	i = 1;
	while (i < ray_count)
	{
		render_3d_projects_walls_arr(press, i, ray_count, press->ray_arr);
		i++;
	}
	mlx_put_image_to_window(press->param->mlx, press->param->win, press->img2->img,
							0, 0);
}
