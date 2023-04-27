/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 14:18:52 by youngski          #+#    #+#             */
/*   Updated: 2023/04/27 14:45:38 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "cub2d.h"

#include <stdio.h> //delete

void	reset_image(t_for_press *press)
{
	mlx_destroy_image(press->param->mlx, press->imgs->img);

	press->imgs->img = mlx_new_image(press->param->mlx, (int)(press->info_mini->scale) * \
			press->info_mini->win_width, (int)(press->info_mini->scale) * \
			press->info_mini->win_height);
    press->imgs->data = (int *)mlx_get_data_addr(press->imgs->img, \
                    &(press->imgs->bpp), &(press->imgs->line_size), &(press->imgs->endian));
	mlx_clear_window(press->param->mlx, press->param->win);

}

int	key_press(int keycode, t_for_press *press)
{
	if (keycode == KEY_A)
		press->meta->player_x--;
	if (keycode == KEY_D)
		press->meta->player_x++;
	if (keycode == KEY_W)
		press->meta->player_y--;
	if (keycode == KEY_S)
		press->meta->player_y++;
	printf("x:y = %d:%d\n", press->meta->player_x, press->meta->player_y);
	reset_image(press);
	render_map(press->param, press->info_mini, press->imgs, press->meta);
    draw_player(press->param, press->info_mini, press->imgs);
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}

void	hooking_func(t_param *par, t_meta_data *met, t_mini_map *info_mi, t_img_2d *im)
{
	t_for_press *press;

	press = (t_for_press *)malloc(sizeof(t_for_press));
	press->param = par;
	press->meta = met;
	press->info_mini = info_mi;
	press->imgs = im;
	mlx_key_hook(par->win, &key_press, press);
}
