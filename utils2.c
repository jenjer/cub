/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/04/20 17:54:50 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_exit(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
	return (1);
}

void	free_spl(char **temp)
{
	int	i;

	i = 0;
	while (temp && temp[i])
	{
		free(temp[i]);
		temp[i] = NULL;
		if (temp[i + 1] == NULL)
			break ;
		i++;
	}
	free(temp);
	temp = NULL;
}

void	add_bits(t_color *color)
{
	color->all = 0;
	color->all += color->red;
	color->all = color->all << 8;
	color->all += color->green;
	color->all = color->all << 8;
	color->all += color->blue;
}

int	make_rgb_bit(t_meta_data *data)
{
	add_bits(data->f_color);
	add_bits(data->c_color);
	return (1);
}
