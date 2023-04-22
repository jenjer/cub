/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_origin_valid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 20:51:09 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/22 20:58:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_space(char *line)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		
}

int	check_original_map(char **map)
{
	int	r;

	r = -1;
	if (check_map_space(map[++r]))
		ft_exit("Invalid map\n");
}