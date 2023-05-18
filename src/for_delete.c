/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:33:17 by youngski          #+#    #+#             */
/*   Updated: 2023/05/18 16:26:36 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_all(t_meta_data meta)
{
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
	print_all(meta);
}

void	leakcheck(void)
{
	system("leaks cub3d");
}
