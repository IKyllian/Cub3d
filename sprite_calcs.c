/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:54:44 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 13:51:58 by kdelport         ###   ########lyon.fr   */
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
	float	ray;
	// float	temp;

	// ptr->sprite[i]->size_x = ptr->sp_txt->width * ptr->sprite[i]->dist;
	// ptr->sprite[i]->size_y = ptr->sp_txt->height * ptr->sprite[i]->dist;
	ray = -ptr->fov.fov + (((float)ptr->fov.fov * 2) / ((float)ptr->info_file.res_x)) * ((float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x);
	if (ptr->sprite[i]->dist > 0)
		ptr->sprite[i]->dist *= cos(deg_rad(1) * ray);
	ray_height = (int)(ptr->info_file.res_y / ptr->sprite[i]->dist);
	ptr->sprite[i]->u_coord = - ((float)ray_height) / 2 + (float)ptr->info_file.res_y / 2 - 2;
	ptr->sprite[i]->b_coord = (float)ray_height / 2 + (float)ptr->info_file.res_y / 2 + 2;
	size = ptr->sprite[i]->b_coord - ptr->sprite[i]->u_coord;
	// ptr->sprite[i]->size_x = ptr->sp_txt->width * ((d_wall - ptr->sprite[i]->dist) / d_wall);
	// ptr->sprite[i]->size_y = ptr->sp_txt->height * ((d_wall - ptr->sprite[i]->dist) / d_wall);
	// if (ptr->sprite[i]->id == 0)
	// 	printf("%iy\t%i\n", i, abs(ptr->sprite[i]->u_coord - ptr->sprite[i]->b_coord));
	
	ptr->sprite[i]->l_coord = (float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x - size / 2;
	ptr->sprite[i]->r_coord = (float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x + size / 2;
	
	// temp = ptr->sprite[i]->r_x - size / 2;
	// temp = atan(temp * tan(ptr->fov.fov * 0.0174533) / ((float)ptr->info_file.res_x / 2)) / 0.0174533;
	// printf("%f\n", temp);
	// if (temp > ptr->fov.fov)
	// 	ptr->sprite[i]->visible = 0;
	// temp = ptr->sprite[i]->r_x + size / 2;
	// temp = atan(temp * tan(ptr->fov.fov * 0.0174533) / ((float)ptr->info_file.res_x / 2)) / 0.0174533;
	// if (temp < -ptr->fov.fov)
	// 	ptr->sprite[i]->visible = 0;

	// if ()
	// 	ptr->sprite[i]->visible = 0;
	// else if ()
	// 	ptr->sprite[i]->visible = 0;
	// if (ptr->sprite[i]->id == 0)
	// 	printf("x\t%i\n", abs(ptr->sprite[i]->l_coord - ptr->sprite[i]->r_coord));
}