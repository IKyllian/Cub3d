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

void	put_wall(int start_ray, int end_ray, t_texture tex, t_window *ptr)
{
	int tex_x;
	int tex_y;

	tex_x = fmodf(ptr->ray.nwall_x, 1) * tex.width;
   if (fmodf(ptr->ray.nwall_x, 1) == 0)
       tex_x = fmodf(ptr->ray.nwall_y, 1) * tex.width;
	tex_y = (ptr->ray.pos - start_ray) * tex.height / (end_ray - start_ray);
	my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos, tex.addr[tex_y * tex.width + tex_x]);
}

t_texture select_texture(t_window *ptr)
{
	if (ptr->ray.side == 1 && ptr->fov.vect_x >= 0)
		return (ptr->e_tex);
	else if (ptr->ray.side == 1 && ptr->fov.vect_x < 0)	
		return (ptr->o_tex);
	else if (!ptr->ray.side && ptr->fov.vect_y >= 0)	
		return (ptr->s_tex);
	else
		return (ptr->n_tex);
}

void	put_ray(int start_ray, int end_ray, t_window *ptr)
{
	int	w_colour;

	ptr->ray.pos = 0;
	if (ptr->ray.dist_x < ptr->ray.dist_y)
		ptr->ray.side = 1;
	//w_colour = ft_trgb(0, 111, 111, 111); //East / West
	else
		ptr->ray.side = 0;
	//w_colour = ft_trgb(0, 0, 111, 111); //North / South
	while (ptr->ray.pos < ptr->info_file.res_y)
	{
		if (ptr->ray.pos < start_ray)
			my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos, ptr->info_file.ceiling);
		else if (ptr->ray.pos >= start_ray && ptr->ray.pos <= end_ray)
		{
			put_wall(start_ray, end_ray, select_texture(ptr), ptr);
			//my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos, w_colour);
		}
		else
			my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos, ptr->info_file.ground);
		ptr->ray.pos++;
	}
	
}

void	ray_cannon(float fish, t_window *ptr)
{
	float	ray_len;
	int		ray_height;
	int		start_ray;
	int		end_ray;
	
	if (ptr->ray.dist_x < ptr->ray.dist_y && ptr->ray.dist_x != 0)
		ray_len = ptr->ray.dist_x * fish;
	else
		ray_len = ptr->ray.dist_y * fish;
	ray_height = (int)((ptr->info_file.res_y / ray_len));
	start_ray = -(ray_height) / 2 + ptr->info_file.res_y / 2;
	if (start_ray < 0)
		start_ray = 0;
	end_ray = ray_height / 2 + ptr->info_file.res_y / 2;
	// if (end_ray >= ptr->info_file.res_y)
	// 	end_ray = ptr->info_file.res_y - 1;
	put_ray(start_ray, end_ray, ptr);
}