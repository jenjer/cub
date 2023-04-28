/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/04/28 18:40:51 by gyopark          ###   ########.fr       */
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

void	do_dfs1(t_meta_data *meta, int r, int c)
{
	const int	dr[4] = {0, 0, -1, 1};
	const int	dc[4] = {-1, 1, 0, 0};
	int			nr;
	int			nc;
	int			i;

	meta->visited[r][c] = 1;
	if (meta->sp_map[r][c] == '1')
		meta->num1--;
	i = -1;
	while (++i < 4)
	{
		nr = r + dr[i];
		nc = c + dc[i];
		if (meta->visited[nr][nc] == 0 && meta->sp_map[nr][nc] == '1')
			do_dfs1(meta, nr, nc);
	}
}

int	dfs1_start(t_meta_data *meta)
{
	int		i;

	meta->visited = (int **)malloc(sizeof(int *) * (meta->height + 2));
	i = 0;
	while (i < meta->height + 2)
	{
		meta->visited[i] = (int *)malloc(sizeof(int) * (meta->max_width + 2));
		memset(meta->visited[i], 0, sizeof(int) * (meta->max_width + 2));
		i++;
	}
	do_dfs1(meta, meta->pos1_r, meta->pos1_c);
	//
	printf("visited array\n");
	i = 0;
	while (i < meta->height + 2)
	{
		int j = 0;
		while (j < meta->max_width + 2)
			printf("%d", meta->visited[i][j++]);
		printf("\n");
		i++;
	}
	//
	printf("num1 after dfs : %d\n", meta->num1);
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

int	is_one_in(t_meta_data *meta, int r, int c)
{
	while (meta->sp_map[++r])
	{
		c = -1;
		while (meta->sp_map[r][++c])
		{
			if (meta->sp_map[r][c] == '1' && meta->visited[r][c] == 0)
			{
				if (check_four_side(meta, r, c))
					return (1);
			}
		}
	}
	return (0);
}

int	map_valid_check(t_meta_data *meta)
{
	int	r;
	int	c;
	int	flag;
	int	first1;

	flag = 0;
	first1 = 0;
	r = -1;
	while (meta->sp_map[++r])
	{
		c = -1;
		while (meta->sp_map[r][++c])
		{
			if (!valid_char_check(meta->sp_map[r][c]))
			{
				ft_exit("Invalid map! 1\n");
			}
			if (meta->sp_map[r][c] == 'X')
			{
				if (map_check_func(meta, r, c))
				{
					ft_exit("Invalid map! 2\n");
				}
			}
			if (meta->sp_map[r][c] == 'N' || meta->sp_map[r][c] == 'S'
				|| meta->sp_map[r][c] == 'E' || meta->sp_map[r][c] == 'W')
			{
				meta->player_x = c;
				meta->player_y = r;
				flag++;
				meta->sp_map[r][c] = '0'; // 0으로 변경사항이 있다.
			}
			if (meta->sp_map[r][c] == '1')
			{
				if (first1 == 0)
				{
					meta->pos1_r = r;
					meta->pos1_c = c;
					first1++;
				}
				meta->num1++;
			}	
		}	
	}
	printf("num1 : %d\n", meta->num1);
	dfs1_start(meta);
	if (meta->num1 != 0)
	{
		if (is_one_in(meta, -1, -1))
			ft_exit("dfs error\n");
	}
	return (flag != 1);
}
