/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/03/28 19:52:27 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

int	map_check_func(t_meta_data *meta, int r, int c)
{
	static int	dr[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
	static int	dc[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
	int			nr;
	int			nc;
	int			i;

	i = -1;
	while (++i < 8)
	{
		nr = r + dr[i];
		nc = c + dc[i];
		if (nr < 0 || nc < 0 || nr >= meta->height + 2
			|| nc >= meta->max_width + 2)
			continue ;
		else if (meta->sp_map[nr][nc] != '1' && meta->sp_map[nr][nc] != 'X')
			return (1);
	}
	return (0);
}

int	valid_char_check(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S'
		|| c == 'W' || c == 'X');
}

int	map_valid_check(t_meta_data meta)
{
	int	r;
	int	c;
	int	flag;

	flag = 0;
	r = -1;
	while (meta.sp_map[++r])
	{
		c = -1;
		while (meta.sp_map[r][++c])
		{
			if (!valid_char_check(meta.sp_map[r][c]))
				return (1);
			if (meta.sp_map[r][c] == 'X')
				if (map_check_func(&meta, r, c))
					return (1);
			if (meta.sp_map[r][c] == 'N' || meta.sp_map[r][c] == 'S'
				|| meta.sp_map[r][c] == 'E' || meta.sp_map[r][c] == 'W')
				flag++;
		}
	}
	return (flag != 1);
}
