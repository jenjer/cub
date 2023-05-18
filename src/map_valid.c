/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark <gyopark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/05/18 21:56:30 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	dfs1_start(t_meta_data *meta)
{
	int		i;

	meta->visited = (int **)malloc(sizeof(int *) * (meta->height + 2));
	i = 0;
	while (i < meta->height + 2)
	{
		meta->visited[i] = (int *)malloc(sizeof(int) * (meta->max_width + 2));
		ft_memset(meta->visited[i], 0, sizeof(int) * (meta->max_width + 2));
		i++;
	}
	do_dfs1(meta, meta->pos1_r, meta->pos1_c);
	i = 0;
	return (0);
}

int	check_four_side(t_meta_data *meta, int r, int c)
{
	const int	dr[4] = {0, 0, -1, 1};
	const int	dc[4] = {-1, 1, 0, 0};
	int			nr;
	int			nc;
	int			i;

	i = -1;
	while (++i < 4)
	{
		nr = r + dr[i];
		nc = c + dc[i];
		if (meta->sp_map[nr][nc] == 'X')
			return (1);
	}
	return (0);
}

void	check_alpha(t_meta_data *meta, int *flag, int r, int c)
{
	if (meta->sp_map[r][c] == 'N' || meta->sp_map[r][c] == 'S'
				|| meta->sp_map[r][c] == 'E' || meta->sp_map[r][c] == 'W')
	{
		meta->player_x = c;
		meta->player_y = r;
		(*flag)++;
		meta->dir = check_cardinal(meta->sp_map[r][c]);
		meta->sp_map[r][c] = '0';
	}
}

void	check_wall_sp_map(t_meta_data *meta, int r, int c, int *first1)
{
	if (meta->sp_map[r][c] == '1')
	{
		if (*first1 == 0)
		{
			meta->pos1_r = r;
			meta->pos1_c = c;
			(*first1)++;
		}
		meta->num1++;
	}	
}

int	map_valid_check(t_meta_data *meta, int r, int flag, int first1)
{
	int	c;

	while (meta->sp_map[++r])
	{
		c = -1;
		while (meta->sp_map[r][++c])
		{
			if (!valid_char_check(meta->sp_map[r][c]))
				ft_exit("Invalid map! 1\n");
			if (meta->sp_map[r][c] == 'X')
			{
				if (map_check_func(meta, r, c))
					ft_exit("Invalid map! 2\n");
			}
			check_alpha(meta, &flag, r, c);
			check_wall_sp_map(meta, r, c, &first1);
		}	
	}
	call_dfs(meta);
	return (flag != 1);
}
