/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyopark < gyopark@student.42seoul.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 11:35:05 by youngski          #+#    #+#             */
/*   Updated: 2023/03/28 19:44:04 by gyopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
