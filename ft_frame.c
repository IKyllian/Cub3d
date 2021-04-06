/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:53:21 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/06 11:01:56 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	img_init(t_window *ptr)
{
	t_image		image;

	image.ptr = mlx_new_image(ptr->mlx, ptr->info_file.res_x,
			ptr->info_file.res_y);
	image.addr = mlx_get_data_addr(image.ptr, &image.bpp, &image.len,
			&image.endian);
	ptr->image = image;
}

void	my_mlx_pixel_put(t_window *ptr, int x, int y, int color)
{
	char	*dst;

	dst = ptr->image.addr + (y * ptr->image.len + x * (ptr->image.bpp / 8));
	*(unsigned int *)dst = color;
}

void	my_mlx_multi_put(t_window *ptr, int x, int y, int color)
{
	int i;

	i = 0;
	while (i < ptr->fov.multi)
	{
		my_mlx_pixel_put(ptr, x, y, color);
		x++;
		i++;
	}
}

int	frame_gen(t_window *ptr)
{
	key_move(ptr);
	sprite_reset(ptr);
	if (ptr->info_file.skybox)
		put_sky(ptr);
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
		ft_error("\0", 0, ptr);
	}
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->image.ptr, 0, 0);
	return (0);
}
