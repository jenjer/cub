/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/20 14:08:21 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_param(t_param *param)
{
	param->win_height = 64;
	param->win_height = 64;
	param->posX = 22;
	param->posY = 11;
	param->dirX = -1.0;
	param->dirY = 0.0;
	param->planeX = 0.0;
	param->planeY = 0.66;
	param->texture = (int **) malloc(sizeof(int *) * 4);
	if (!(param->texture))
		return (1);
	param->moveSpeed = 0.05;
	param->rotSpeed = 0.05;
	return (0);
}

int	param_texture_init(int **texture, int width, int height)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture[i] = (int *) malloc(sizeof(int) * (width * height));
		if (!texture[i])
			return (1);
		i++;
	}
	i = 0;
	while (i < 4)
		memset(texture[i++], 0, sizeof(int) * (width * height));
	return (0);
}
/*

void	load_image(t_param *param, int *texture, char *path, t_img *img)
{
	int	i;
	int	j;

	j = 0;
	img->img = mlx_xpm_file_to_image(param->mlx, path, \
	&img->img_width, &img->img_height);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
	&img->size_l, &img->endian);
	while (j < img->img_height)
	{
		i = 0;
		while (i < img->img_width)
			texture[img->img_width * j + i] = img->data[img->img_width * j + i];
	}
	mlx_destroy_image(param->mlx, img->img);
}
*/
/*
t_img	load_texture(t_param *param)
{
	t_img	img;

	load_image(param, param->texture[0], "texture/1.xpm", &img);
	load_image(param, param->texture[1], "texture/2.xpm", &img);
	load_image(param, param->texture[2], "texture/3.xpm", &img);
	load_image(param, param->texture[3], "texture/4.xpm", &img);
	return (img);
}
*/

// ----
int	main_loop(t_param *param)
{
	param = NULL;
	while (1)
		;
}

int	key_press(int key, t_param *param)
{
	key = 0;
	param = NULL;
	while (1)
		;
}
// ----

int	map_cast(t_param *param, t_meta_data data)
{	
	if (fill_param(param))
		return (1);
	if (param_texture_init(param->texture, param->win_width, param->win_height))
		return (1);
	param->mlx = mlx_init();
	param->win = mlx_new_window(param->mlx, 1920, 1080, "cub3d"); 
	// param->img = load_texture(param);
	param->img.img = mlx_new_image(param->mlx, 1920, 1080);
	param->img.data = mlx_get_data_addr(param->img.img, &(param->img.bpp), \
	&(param->img.size_l), &(param->img.endian));

	mlx_loop_hook(param->mlx, &main_loop, param);
	mlx_hook(param->win, X_EVENT_KEY_PRESS, 0, &key_press, param);
	mlx_loop(param->mlx);
	/*
	info.win = mlx_new_window(info.mlx, width, height, "mlx");

	info.img.img = mlx_new_image(info.mlx, width, height);
	info.img.data = (int *)mlx_get_data_addr(info.img.img, &info.img.bpp, &info.img.size_l, &info.img.endian);

	mlx_loop_hook(info.mlx, &main_loop, &info);
	mlx_hook(info.win, X_EVENT_KEY_PRESS, 0, &key_press, &info);

	mlx_loop(info.mlx);
	*/
	return (0);
}
