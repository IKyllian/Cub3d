/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:53:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:13:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_fov(t_window *ptr)
{
	t_fov	fov;

	fov.fov = 0;
	fov.multi = 0;
	fov.angle = 0;
	fov.vect_x = 0;
	fov.vect_y = 0;
	fov.dist = NULL;
	fov.mod = 0;
	fov.shade = NULL;
	ptr->fov = fov;
}

void	init_struct_img(t_window *ptr)
{
	t_image	image;

	image.ptr = NULL;
	image.addr = NULL;
	image.bpp = 0;
	image.len = 0;
	image.endian = 0;
	ptr->image = image;
}

void	fill_img_struct(t_window *ptr)
{
	ptr->image.ptr = mlx_new_image(ptr->mlx, ptr->info_file.res_x,
			ptr->info_file.res_y);
	ptr->image.addr = mlx_get_data_addr(ptr->image.ptr, &ptr->image.bpp,
			&ptr->image.len, &ptr->image.endian);
}
