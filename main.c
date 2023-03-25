/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/03/25 17:33:09 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h> //for printf

void	print_map(t_meta_data meta)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (meta.map[i])
	{
		printf("%s", meta.map[i]);
		i++;
	}
	i = 0;
	printf("  (null)\n\n");
	while (meta.sp_map[i])
	{
		printf("%s", meta.sp_map[i]);
		i++;
	}
}

void	leakcheck(void)
{
	system("leaks a.out");
}

void	init_meta_data(char *name, t_meta_data *meta)
{
	meta->fd = open(name, O_RDONLY);
	meta->height = 0;
	meta->add_height = 0;
	meta->map = 0;
	meta->sp_map = 0;
	meta->max_width = 0;
}

int	main(int argc, char **argv)
{
	t_meta_data	meta;

	atexit(leakcheck);
	init_meta_data(argv[1], &meta);
	if (argc != 2 || ft_strrncmp(argv[1], ".cub", 4))
		return (write(2, "Invalid Argument!\n", 18) * 0 + 1);
	if (map_init(&meta, 0, NULL, 0))
		return (write(2, "File open err!\n", 15) * 0 + 1);
	print_map(meta);
	//	if (!map_valid_check(meta))
	//		return (write(2, "Invalid map!\n", 13) * 0 + 1);
	return (free_all(meta));
}
