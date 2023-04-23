/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/04/23 21:52:31 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message, int code)
{
	write(2, message, ft_strlen(message));
	exit(code);
}

void	skip_space(char **str)
{
	while (*str[0] == '\t' || *str[0] == '\v' || \
			*str[0] == '\f' || *str[0] == '\r' || *str[0] == ' ')
		(*str)++;
}

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			;
		else
			return (1);
		i++;
	}
	return (0);
}

int	map_free_all(t_meta_data meta)
{
	int		i;

	i = 0;
	if (meta.f_color)
		free(meta.f_color);
	if (meta.c_color)
		free(meta.c_color);
	if (meta.north)
		free(meta.north);
	if (meta.south)
		free(meta.south);
	if (meta.west)
		free(meta.west);
	if (meta.east)
		free(meta.east);
	while (meta.map[i])
		free(meta.map[i++]);
	free(meta.map);
	i = 0;
	while (meta.sp_map[i])
		free(meta.sp_map[i++]);
	i = 0;
	free(meta.sp_map);
	return (0);
}

int	ft_strrncmp(char *s1, char *s2, int n)
{
	int	i;

	i = ft_strlen(s1) - 1;
	if (i < 4)
		return (1);
	n--;
	while (s1[i] == s2[n])
	{
		if (i == 0 || n == 0)
			break ;
		i--;
		n--;
	}
	if (i && s1[i - 1] == '/')
		return (1);
	if (s1[i] == s2[n])
		return (0);
	else
		return (1);
}
