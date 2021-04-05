/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:07:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/05 15:51:27 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inverse_cam(char dir, t_window *ptr)
{
	if (dir == 'B')
	{
		ptr->fov.vect_x *= -1;
		ptr->fov.vect_y *= -1;
	}
}

int	wall_check(float x, float y, t_window *ptr)
{
	if (ptr->info_file.map[(int)y][(int)x] == '1'
		|| ptr->info_file.map[(int)y][(int)x] == '2'
		|| ptr->info_file.map[(int)y][(int)x] == '4')
		return (0);
	else if (ptr->info_file.map[(int)y][(int)x] == '5')
	{
		ptr->player.health -= 20;
	}
	else if (ptr->info_file.map[(int)y][(int)x] == '6')
	{
		ptr->player.health += 20;
	}
	return (1);
}
