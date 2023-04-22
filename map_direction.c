/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/22 19:58:26 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_direction(t_meta_data *meta)
{
	if (!meta->north || !meta->south || !meta->east || !meta->west)
		return (1);
	if (meta->f_color->red == -1 || meta->f_color->green == -1
		|| meta->f_color->blue == -1)
		return (1);
	if (meta->c_color->red == -1 || meta->c_color->green == -1
		|| meta->c_color->blue == -1)
		return (1);
	return (0);
}

int	see_flag(t_meta_data *meta, char *tmp, int flag)
{
	int	fd;

	if (flag == 5 || flag == 6)
	{
		if (add_color(meta, tmp, flag))
			return (1);
		return (0);
	}
	fd = open(tmp, O_RDONLY);
	if (fd == -1)
		return (1);
	if (flag == 1)
		meta->north = ft_strdup(tmp);
	else if (flag == 2)
		meta->south = ft_strdup(tmp);
	else if (flag == 3)
		meta->west = ft_strdup(tmp);
	else if (flag == 4)
		meta->east = ft_strdup(tmp);
	return (0);
}

void	make_flag(char *line, int *flag, char **tmp)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		*flag = 1;
	else if (ft_strncmp(line, "SO", 2) == 0)
		*flag = 2;
	else if (ft_strncmp(line, "WE", 2) == 0)
		*flag = 3;
	else if (ft_strncmp(line, "EA", 2) == 0)
		*flag = 4;
	else if (ft_strncmp(line, "F", 1) == 0)
		*flag = 5;
	else if (ft_strncmp(line, "C", 1) == 0)
		*flag = 6;
	if (*flag < 5)
		*tmp += 2;
	else
		(*tmp)++;
}

int	add_direction(t_meta_data *meta, char *line)
{
	int		flag;
	char	*tmp;
	char	*for_free;

	flag = 0;
	tmp = ft_strdup(line);
	for_free = tmp;
	if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0
		|| ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0
		|| ft_strncmp(line, "F", 1) == 0 || ft_strncmp(line, "C", 1) == 0)
	{
		make_flag(line, &flag, &tmp);
		skip_space(&tmp);
	}
	else
		return (1);
	if (see_flag(meta, tmp, flag))
		return (1);
	free(for_free);
	for_free = NULL;
	return (0);
}

int	map_direction_init(t_meta_data *meta)
{
	int		flag;
	char	*line;

	flag = 0;
	if (meta->fd <= 0)
		return (1);
	while (1)
	{
		line = get_next_line(meta->fd);
		if (!line)
			return (1);
		if (ft_strlen(line) == 1 && line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (!add_direction(meta, line))
			flag++;
		else
		{
			free(line);
			return (1);
		}
		free(line);
		if (flag == 6)
			break ;
	}
	if (check_direction(meta))
		return (1);
	return (0);
}
