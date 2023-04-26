/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:18:52 by youngski          #+#    #+#             */
/*   Updated: 2023/04/26 14:32:46 by youngski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub2d.h"



#include <stdio.h> //delete
int	key_press(int keycode, t_meta_data *meta)
{
	if (keycode == KEY_A)
		meta->player_x--;
	if (keycode == KEY_D)
		meta->player_x++;
	if (keycode == KEY_W)
		meta->player_y--;
	if (keycode == KEY_S)
		meta->player_y++;
	printf("x:y = %d:%d\n", meta->player_x, meta->player_y);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	hooking_func(t_param *param, t_meta_data *meta)
{
	mlx_hook(param->win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, meta);

}
