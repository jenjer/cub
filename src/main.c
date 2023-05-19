/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/05/19 15:28:24 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	meta_data_setting_zero(t_meta_data *meta)
{
	meta->height = 0;
	meta->add_height = 0;
	meta->map = 0;
	meta->sp_map = 0;
	meta->max_width = 0;
	meta->f_color = NULL;
	meta->c_color = NULL;
	meta->player_x = 0;
	meta->player_y = 0;
	meta->pos1_r = 0;
	meta->pos1_c = 0;
	meta->num1 = 0;
	meta->dir = 0;
	meta->visited = NULL;
}

void	init_meta_data(char *name, t_meta_data *meta)
{
	int		i;

	i = 0;
	meta->fd = open(name, O_RDONLY);
	if (meta->fd <= 0)
		ft_exit("file open error!\n");
	meta->tex = (t_texture *)malloc(sizeof(t_texture) * 4);
	if (!meta->tex)
		ft_exit("texture allocation failed!\n");
	while (i < 4)
	{
		meta->tex[i].tex_path = NULL;
		meta->tex[i].texture = NULL;
		meta->tex->width = 0.0;
		meta->tex->height = 0.0;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_meta_data	meta;
	t_param		param;

	if (argc != 2 || ft_strrncmp(argv[1], ".cub", 4))
		return (ft_exit("Invalid Argument\n"));
	ft_memset(&meta, 0, sizeof(t_meta_data));
	ft_memset(&param, 0, sizeof(t_param));
	init_meta_data(argv[1], &meta);
	/*
	map_direction_init(&meta, 0, NULL);
	map_init(&meta, NULL, 0, 0);
	map_valid_check(&meta, -1, 0, 0);
	make_rgb_bit(&meta);
	map_cast(&param, &meta);
	*/

	if (map_direction_init(&meta, 0, NULL) || map_init(&meta, NULL, 0, 0))
		return (ft_exit("file open error\n"));
	if (map_valid_check(&meta, -1, 0, 0))
		return (ft_exit("Invalid map\n"));
	if (make_rgb_bit(&meta) && map_cast(&param, &meta))
		exit(1);
	return (map_free_all(meta, 0));
}
	// print_map(meta);
