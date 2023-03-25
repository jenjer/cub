/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/03/25 20:47:08 by gyopark          ###   ########.fr       */
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
}

void	leakcheck(void)
{
	system("leaks cub3d");
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

	// atexit(leakcheck);
	init_meta_data(argv[1], &meta);
	if (argc != 2 || ft_strrncmp(argv[1], ".cub", 4))
		return (write(2, "Invalid Argument!\n", 18) * 0 + 1);
	if (map_init(&meta, NULL, 0))
		return (write(2, "File open err!\n", 15) * 0 + 1);
	printf("height : %d\n", meta.height);
	printf("width : %d\n\n", meta.max_width);
	print_map(meta);
	//map_init에서 gnl할 때마다 0, 1, ' ', \n, 동서남북 제외 다른거 나오면 에러
	if (map_valid_check(&meta))
		return (write(2, "Invalid map!\n", 13) * 0 + 1);
	write(1, "valid\n", ft_strlen("valid\n"));
	return (free_all(meta));
}
