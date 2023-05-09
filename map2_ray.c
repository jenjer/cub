/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:20:14 by gyopark           #+#    #+#             */
/*   Updated: 2023/05/09 19:58:59 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void	setting_ray_location(t_press *press, double *x, double *y)
{
	int	old_x;
	int	old_y;

	old_x = *x;
	old_y = *y;
	if (press->map2->m_dir == LU)
	{
		*x = (int)(press->map2->scale * old_x);
		*y = (int)(press->map2->scale * old_y);
	}
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
			// setting_ray_location(press, &ray_x, &ray_y);
			press->img2->data[(GAME_WIDTH * \
				(int)((ray_y) * (press->map2->mts))) + \
				(int)((ray_x) * (press->map2->mts))] = 0xff0000;
	
		}
		else
			break ;
		ray_y += (dy / (press->map2->mts));
		ray_x += (dx / (press->map2->mts));
	}
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cal_distance(t_press *press, t_dp_ray *hv)
{
	if (hv->found_wallhit == 1)
		hv->distance = distance_between_points(press->player2->x, \
		press->player2->y, hv->wall_hitx, hv->wall_hity);
	else
		hv->distance = DBL_MAX;
}

void	cal_ray(t_press *press, t_dp_ray *hv)
{
	double	next_touch_x;
	double	next_touch_y;
	double	check_touch_y;

	next_touch_x = hv->xintercept;
	next_touch_y = hv->yintercept;
	check_touch_y = 0;
	while (next_touch_x >= 0 && next_touch_x <= GAME_WIDTH && next_touch_y >= 0 \
				&& next_touch_y <= GAME_HEIGHT)
	{
		if (press->ray2->is_ray_facingup)
			check_touch_y = 1;
		if (check_wall_light(press, next_touch_x, next_touch_y - check_touch_y))
		{
			hv->found_wallhit = 1;
			hv->wall_hitx = next_touch_x;
			hv->wall_hity = next_touch_y;
			break ;
		}
		else
		{
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
	vert->xintercept = floor(press->player2->x / press->map2->mts) * press->map2->mts;
	if (!press->ray2->is_ray_facingright)
		vert->xintercept += press->map2->mts;
	vert->yintercept = press->player2->y + (vert->xintercept - press->player2->x) * tan(press->ray2->ray_angle);
	vert->xstep = press->map2->mts;
	if (!press->ray2->is_ray_facingleft)
		vert->xstep *= -1;
	vert->ystep = press->map2->mts * tan(press->ray2->ray_angle);
	if (!press->ray2->is_ray_facingleft && vert->ystep > 0)
		vert->ystep *= -1;
	if (!press->ray2->is_ray_facingright && vert->ystep < 0)
		vert->ystep *= -1;
	cal_ray(press, vert);
}

void	cal_horz_ray(t_press *press, t_dp_ray *horz)
{
	horz->found_wallhit = 0;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(press->player2->y / press->map2->mts) * press->map2->mts;
	if (!press->ray2->is_ray_facingdown)
		horz->yintercept += press->map2->mts;
	horz->xintercept = press->player2->x + (horz->yintercept - press->player2->y) / tan(press->ray2->ray_angle);
	horz->ystep = press->map2->mts;
	if (!press->ray2->is_ray_facingup)
		horz->ystep *= -1;
	horz->xstep = press->map2->mts / tan(press->ray2->ray_angle);
	if (!press->ray2->is_ray_facingleft && horz->xstep > 0)
		horz->xstep *= -1;
	if (!press->ray2->is_ray_facingright && horz->xstep < 0)
		horz->xstep *= -1;
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
	ray2->is_ray_facingdown = (ray2->ray_angle > 0 && ray2->ray_angle < PI);
	if (ray2->is_ray_facingdown)
		ray2->is_ray_facingup = 0;
	else
		ray2->is_ray_facingup = 1;
	ray2->is_ray_facingright = (ray2->ray_angle < 0.5 * PI || ray2->ray_angle > 1.5 * PI);
	ray2->is_ray_facingleft = !(ray2->is_ray_facingright);
}

void	draw_one_ray(t_press *press, double angle, int ray_num)
{
	t_dp_ray	horz;
	t_dp_ray	vert;

	ray_init(press->ray2, angle);
	cal_horz_ray(press, &horz);
	cal_vert_ray(press, &vert);
	if (vert.distance < horz.distance)
	{
		press->ray2->wall_hit_x = vert.wall_hitx;
		press->ray2->wall_hit_y = vert.wall_hity;
		press->ray2->distance = vert.distance;
		press->ray2->was_hit_vertical = 1;
	}
	else
	{
		press->ray2->wall_hit_x = horz.wall_hitx;
		press->ray2->wall_hit_y = horz.wall_hity;
		press->ray2->distance = horz.distance;
		press->ray2->was_hit_vertical = 0;
	}
	draw_line(press, press->player2->x, press->player2->y,
		press->ray2->wall_hit_x, press->ray2->wall_hit_y);
	render_3d_projects_walls(press, ray_num);
	ray_num = 0;
}

void	draw_ray(t_press *press)
{
	double	angle;
	double	max_angle;
	double	ray_range;
	int		ray_count;
	int		i;

	i = 1;
	ray_range = PI / 3.0; // 60도 (플레이어의 시야각)
	ray_count = 121;
	angle = press->player2->rotation_angle; // 플레이어가 바라보는 각도
	max_angle = press->player2->rotation_angle + (ray_range / 2.0);
	// 시야각이 60라면, 플레이어의 최대 각도는 +30도가 된다.
	while (i < ray_count)
	{
		draw_one_ray(press, angle - (ray_range / 2.0), i);
		angle += ray_range / ray_count;
		i++;
	}
	mlx_put_image_to_window(press->param->mlx, press->param->win, press->img2->img,
							0, 0);
}
