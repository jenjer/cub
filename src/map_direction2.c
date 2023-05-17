/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_direction2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <youngski@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:34:13 by youngski          #+#    #+#             */
/*   Updated: 2023/05/17 20:39:22 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	freeing_line_and_fin(char *line)
{
	free(line);
	return (ft_exit("file open error\n"));
}
