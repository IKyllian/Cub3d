/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:23:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/23 10:23:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_ray(int index, int start_ray, int end_ray, t_window *ptr)
{
	int y;
	int	w_colour;

	y = 0;
	if (ptr->player.dist_x < ptr->player.dist_y)
		w_colour = ft_trgb(0, 111, 111, 111);
	else
		w_colour = ft_trgb(0, 0, 111, 111);
	while (y < ptr->info_file.res_y)
	{
		if (y < start_ray)
			my_mlx_pixel_put(ptr, index, y, ptr->info_file.ceiling);
		else if (y >= start_ray && y <= end_ray)
			my_mlx_pixel_put(ptr, index, y, w_colour);
		else
			my_mlx_pixel_put(ptr, index, y, ptr->info_file.ground);
		y++;
	}
	
}

void	ray_cannon(float fish, int index, t_window *ptr)
{
	float	ray_len;
	int		ray_height;
	int		start_ray;
	int		end_ray;
	
	if (ptr->player.dist_x < ptr->player.dist_y && ptr->player.dist_x != 0)
		ray_len = ptr->player.dist_x * fish;
	else
		ray_len = ptr->player.dist_y * fish;
	
	// if (x >= 0 || y >= 0)
	// 	ray_len = sqrtf (exp2f(x - ptr->player.x) + exp2f(y - ptr->player.y));
	// else if (x < 0 || y < 0)
	// 	ray_len = len;
	ray_height = (int)((ptr->info_file.res_y / ray_len));
	start_ray = -(ray_height) / 2 + ptr->info_file.res_y / 2;
	if (start_ray < 0)
		start_ray = 0;
	end_ray = ray_height / 2 + ptr->info_file.res_y / 2;
	if (end_ray >= ptr->info_file.res_y)
		end_ray = ptr->info_file.res_y - 1;
	put_ray(index, start_ray, end_ray, ptr);
}