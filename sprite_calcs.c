/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:54:44 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/01 11:36:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_dist(t_window *ptr)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		x = ptr->sprite[i]->x;
		y = ptr->sprite[i]->y;
		ptr->sprite[i]->dist = sqrtf(powf(x - ptr->player.pos_x, 2)
				+ powf(y - ptr->player.pos_y, 2));
		i++;
	}
}

void	sprite_sizer(int i, t_window *ptr)
{
	int		ray_height;
	int		size;
	float	fish_dist;
	float	ray;
	float	ratio;

	if (ptr->input.crouch)
		ratio = 2.3;
	else
		ratio = 2;
	ray = -ptr->fov.fov + (((float)ptr->fov.fov * 2)
			/ ((float)ptr->info_file.res_x))
		* ((float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x);
	fish_dist = ptr->sprite[i]->dist * cos(deg_rad(1) * ray);
	ray_height = (int)(ptr->info_file.res_y / fish_dist);
	ptr->sprite[i]->u_coord = - ((float)ray_height) / 2
		+ (float)ptr->info_file.res_y / ratio - 2;
	ptr->sprite[i]->b_coord = (float)ray_height / 2
		+ (float)ptr->info_file.res_y / ratio + 2;
	size = ptr->sprite[i]->b_coord - ptr->sprite[i]->u_coord;
	ptr->sprite[i]->l_coord = (float)ptr->info_file.res_x / 2
		+ ptr->sprite[i]->r_x - size / 2;
	ptr->sprite[i]->r_coord = (float)ptr->info_file.res_x / 2
		+ ptr->sprite[i]->r_x + size / 2;
}

void	sprite_disable(int i, t_window *ptr)
{
	if (ptr->sprite[i]->angle + 0.2 < -ptr->fov.fov * 0.0174533
		|| ptr->sprite[i]->angle - 0.2 > ptr->fov.fov * 0.0174533)
		ptr->sprite[i]->visible = 0;
}