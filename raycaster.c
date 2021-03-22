/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:23:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/22 11:14:15 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_wall(t_texture tex, t_window *ptr)
{
	int	tex_x;
	int	tex_y;

	tex_x = fmodf(ptr->ray.nwall_x, 1) * tex.width;
	if (fmodf(ptr->ray.nwall_x, 1) == 0)
		tex_x = fmodf(ptr->ray.nwall_y, 1) * tex.width;
	tex_y = (ptr->ray.pos - ptr->ray.u_wall) * tex.height
		/ (ptr->ray.l_wall - ptr->ray.u_wall);
	if (tex_y > tex.height - 1)
		tex_y -= 1;
	my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
		tex.addr[tex_y * tex.width + tex_x]);
}

t_texture	select_tex(t_window *ptr)
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

void	put_ray(t_window *ptr)
{
	ptr->ray.pos = 0;
	if (ptr->ray.dist_x < ptr->ray.dist_y)
		ptr->ray.side = 1;
	else
		ptr->ray.side = 0;
	while (ptr->ray.pos < ptr->info_file.res_y)
	{
		if (ptr->ray.pos < ptr->ray.u_wall)
			my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
				ptr->info_file.ceiling);
		else if (ptr->ray.pos >= ptr->ray.u_wall
			&& ptr->ray.pos <= ptr->ray.l_wall)
			put_wall(select_tex(ptr), ptr);
		else
			my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
				ptr->info_file.ground);
		ptr->ray.pos++;
	}
}

void	ray_cannon(float fish, t_window *ptr)
{
	float	ray_len;
	int		ray_height;

	if (ptr->ray.dist_x < ptr->ray.dist_y && ptr->ray.dist_x != 0)
		ray_len = ptr->ray.dist_x * fish;
	else
		ray_len = ptr->ray.dist_y * fish;
	ptr->fov.dist[ptr->ray.id] = ray_len;
	ray_height = (int)((ptr->info_file.res_y / ray_len)) + 1;
	ptr->ray.u_wall = - ((float)ray_height) / 2
		+ (float)ptr->info_file.res_y / 2;
	ptr->ray.l_wall = (float)ray_height / 2 + (float)ptr->info_file.res_y / 2;
	put_ray(ptr);
}
