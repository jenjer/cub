/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/03/25 16:17:47 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	free_all(t_meta_data meta)
{
	int		i;

	i = 0;
	while (meta.map[i])
		free(meta.map[i++]);
	free(meta.map);
	i = 0;
	while (meta.sp_map[i])
		free(meta.sp_map[i++]);
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

