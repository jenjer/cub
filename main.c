/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/05/15 18:52:41 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_map(t_meta_data meta)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (meta.map && meta.map[i])
	{
		printf("%s\n", meta.map[i]);
		i++;
	}
	i = 0;
	printf("  (null)\n\n");
	while (meta.sp_map[i])
	{
		printf("%s\n", meta.sp_map[i]);
		i++;
	}
	printf("height : %d\n", meta.height);
	printf("max_width : %d\n", meta.max_width);
	printf("add_height : %d\n", meta.add_height);
	printf("tex[0](north) : %s\n", meta.tex[0].tex_path);
	printf("tex[1](south) : %s\n", meta.tex[1].tex_path);
	printf("tex[2](west) : %s\n", meta.tex[2].tex_path);
	printf("tex[3](east) : %s\n", meta.tex[3].tex_path);
	printf("F RED : %d\n", meta.f_color->red);
	printf("F GREEN : %d\n", meta.f_color->green);
	printf("F BLUE : %d\n", meta.f_color->blue);
	printf("C RED : %d\n", meta.c_color->red);
	printf("C GREEN : %d\n", meta.c_color->green);
	printf("C BLUE : %d\n", meta.c_color->blue);
	printf("player X : %d\n", meta.player_x);
	printf("player Y : %d\n", meta.player_y);
}

void	leakcheck(void)
{
	system("leaks cub3d");
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
	meta->visited = NULL;
}

int	main(int argc, char **argv)
{
	t_meta_data	meta;
	t_param			*param;

	param = (t_param *)malloc(sizeof(t_param));
	if (!param)
		ft_exit("parameter allocation error!\n");
	memset(param, 0, sizeof(t_param));
	// atexit(leakcheck);
	init_meta_data(argv[1], &meta);
	if (argc != 2 || ft_strrncmp(argv[1], ".cub", 4))
		return (ft_exit("Invalid Argument\n"));
	if (map_direction_init(&meta) || map_init(&meta, NULL, 0))
		return (ft_exit("file open error\n"));
	if (map_valid_check(&meta))
		return (ft_exit("Invalid map\n"));
	print_map(meta);
	if (make_rgb_bit(&meta) && map_cast(param, &meta))
		exit(1);
	write(1, "valid\n", ft_strlen("valid\n"));
	// exit(0);
	return (map_free_all(meta, param));
}
