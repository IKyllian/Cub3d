/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 10:47:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 14:47:59 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calcul_skybox_angle(t_window *ptr)
{
	ptr->fov.angle = rad_deg(atan(ptr->fov.vect_y / ptr->fov.vect_x));
	if (ptr->fov.vect_x > 0 && ptr->fov.vect_y < 0)
		ptr->fov.angle += 360;
	if (ptr->fov.vect_x < 0 && ptr->fov.vect_y < 0)
		ptr->fov.angle += 180;
	if (ptr->fov.vect_x < 0 && ptr->fov.vect_y > 0)
		ptr->fov.angle += 180;
}

void	put_sky(t_window *ptr)
{
	int	tex_x;
	int	tex_y;
	int	x;
	int	y;

	y = 0;
	calcul_skybox_angle(ptr);
	while (y < ptr->info_file.res_y / 2)
	{
		x = 0;
		while (x < ptr->info_file.res_x)
		{
			tex_x = x * (ptr->skybox.width / 4) / ptr->info_file.res_x + \
				(ptr->skybox.width * ptr->fov.angle / 360);
			tex_y = y * (ptr->skybox.height / 3) / ptr->info_file.res_y + \
				ptr->skybox.height / 3;
			if (ptr->skybox.addr[tex_y * ptr->skybox.width + tex_x])
				my_mlx_pixel_put(ptr, x, y, \
					ptr->skybox.addr[tex_y * ptr->skybox.width + tex_x]);
			x++;
		}
		y++;
	}
}
