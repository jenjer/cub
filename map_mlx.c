/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:42:38 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/22 19:58:14 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	param_init(char *argv1, t_param *param)
{
	param->fd = open(argv1, O_RDONLY);
	if (param->fd <= 0)
		return ;
	param->mlx = mlx_init();
	param->win = NULL;
}
