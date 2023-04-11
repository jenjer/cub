/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/04/08 15:32:21 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	deep_copy_space(char *sp_map, char *map, int width)
{
	int		i;
	int		idx;

	idx = 0;
	i = 0;
	while (++i < width + 1)
	{
		if (map[idx] == '\n' || map[idx] == '\0')
			break ;
		if (map[idx] != ' ')
			sp_map[i] = map[idx];
		idx++;
	}
}

void	fill_sp_map(char *sp_map, int idx)
{
	int	i;

	i = 0;
	while (i < idx - 1)
	{
		sp_map[i] = 'X';
		i++;
	}
	sp_map[idx - 1] = '\0';
}

void	make_sp_map(t_meta_data *meta)
{
	int		i;
	int		idx;
	char	**temp_sp_map;

	i = -1;
	temp_sp_map = meta->sp_map;
	meta->sp_map = (char **)malloc(sizeof(char *) * (meta->height + 3));
	meta->sp_map[meta->height + 2] = 0;
	while (++i < meta->height + 2)
	{
		meta->sp_map[i] = (char *)malloc(sizeof(char) * meta->max_width + 3);
		fill_sp_map(meta->sp_map[i], meta->max_width + 3);
	}
	i = 0;
	idx = 0;
	while (++i < meta->height + 1)
		deep_copy_space(meta->sp_map[i], meta->map[idx++], meta->max_width);	
	if (temp_sp_map)
		free(temp_sp_map);
}

int	map_init(t_meta_data *meta, char **tmp_map, int idx)
{
	char	*line;

	while (1)
	{
		line = get_next_line(meta->fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (meta->max_width < (int) ft_strlen(line))
			meta->max_width = ft_strlen(line);
		tmp_map = meta->map;
		meta->map = (char **)malloc(sizeof(char *) * (meta->height + 2));
		meta->map[meta->height + 1] = 0;
		idx = -1;
		while (++idx < meta->height)
			meta->map[idx] = tmp_map[idx];
		meta->map[idx] = line;
		if (tmp_map)
			free(tmp_map);
		meta->height++;
	}
	make_sp_map(meta);
	return (0);
}
