/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:42:35 by gyopark           #+#    #+#             */
/*   Updated: 2023/04/22 20:46:05 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main_loop(t_param *param)
{
	param = NULL;
	while (1)
		;
}

int	key_press(int key, t_param *param)
{
	key = 0;
	param = NULL;
	while (1)
		;
}
// ------- //

// void	rid_spaces(t_meta_data *data)
// {
// 	int	i;
// 	int	start;
// 	int	fin;
// 	int	cnt;

// 	i = 0;
// 	start = 0;
// 	while (data->map[i])
// 	{
// 		if (data->map[i][0] != '\n')
// 		{
// 			if (start == 0)
// 				start = i;
// 			fin = i;
// 			cnt++;
// 		}
// 	}
// 	i = start;
// 	while (i <= cnt)
// 	{
		
// 	}
// }

int	map_cast(t_param *param, t_meta_data data)
{	
	(void) param;
	(void) data;
	return (0);
}
