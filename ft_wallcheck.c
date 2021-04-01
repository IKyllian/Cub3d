/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:07:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/01 10:13:51 by kdelport         ###   ########lyon.fr   */
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
		|| ptr->info_file.map[(int)y][(int)x] == '2')
		return (0);
	return (1);
}
