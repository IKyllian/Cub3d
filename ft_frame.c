/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:53:21 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/12 14:47:30 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_init(t_window *ptr)
{
	t_image		image;

	image.ptr = mlx_new_image(ptr->mlx, ptr->info_file.res_x, ptr->info_file.res_y);
	image.addr = mlx_get_data_addr(image.ptr, &image.bpp, &image.len, &image.endian);
	ptr->image = image;
	//return (image);
}

void	my_mlx_pixel_put(t_window *ptr, int x, int y, int color)
{
	char	*dst;

	dst = ptr->image.addr + (y * ptr->image.len + x * (ptr->image.bpp / 8));
	*(unsigned int *)dst = color;
}

int	frame_gen(t_window *ptr)
{
	//mlx_clear_window(ptr->ptr, ptr->win);
	put_fov(ptr);
	if (ptr->info_file.res_x > 500 && ptr->info_file.res_y > 500)
	{
		display_map(ptr);
		display_player(ptr);
	}
	sprite_check(ptr);
	if (ptr->save == 1)
	{
		create_bitmap(ptr);
		exit(1);
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->image.ptr, 0, 0);
	return (0);
}