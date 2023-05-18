/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/05/18 21:57:46 by gyopark          ###   ########.fr       */
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
	int		tex_size;

	i = 0;
	tex_size = 4;
	meta->fd = open(name, O_RDONLY);
	meta->tex = (t_texture *)malloc(sizeof(t_texture) * tex_size);
	while (i < tex_size)
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
	t_param		*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		ft_exit("parameter allocation error!\n");
	ft_memset(&meta, 0, sizeof(t_meta_data));
	ft_memset(param, 0, sizeof(t_param));
	init_meta_data(argv[1], &meta);
	if (argc != 2 || ft_strrncmp(argv[1], ".cub", 4))
		return (ft_exit("Invalid Argument\n"));
	if (map_direction_init(&meta, 0, NULL) || map_init(&meta, NULL, 0, 0))
		return (ft_exit("file open error\n"));
	if (map_valid_check(&meta, -1, 0, 0))
		return (ft_exit("Invalid map\n"));
	// print_map(meta);
	if (make_rgb_bit(&meta) && map_cast(param, &meta))
		exit(1);
	write(1, "valid\n", ft_strlen("valid\n"));
	return (map_free_all(meta, param, 0));
}
