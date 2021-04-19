/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:23:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/10 16:03:55 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_wall(t_texture tex, t_window *ptr)
{
	int	tex_x;
	int	tex_y;
	int	colour;

	tex_x = fmodf(ptr->ray.nwall_x, 1) * tex.width;
	if (fmodf(ptr->ray.nwall_x, 1) == 0)
		tex_x = fmodf(ptr->ray.nwall_y, 1) * tex.width;
	tex_y = (ptr->ray.pos - ptr->ray.u_wall) * tex.height
		/ (ptr->ray.l_wall - ptr->ray.u_wall);
	if (tex_y > tex.height - 1)
		tex_y -= 1;
	colour = trgbmod(tex.addr[tex_y * tex.width + tex_x], ptr->fov.mod);
	my_mlx_multi_put(ptr, ptr->ray.id, ptr->ray.pos, colour);
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
	int	ratio;

	ratio = 0;
	ptr->ray.side = 0;
	if (ptr->input.crouch)
		ratio = (int)(ptr->info_file.res_y * 0.07);
	ptr->ray.pos = 0;
	if (ptr->ray.dist_x < ptr->ray.dist_y)
		ptr->ray.side = 1;
	while (ptr->ray.pos < ptr->info_file.res_y)
	{
		if (ptr->ray.pos < ptr->ray.u_wall && !ptr->info_file.skybox)
			my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
				ptr->fov.shade[ptr->ray.pos + ratio]);
		if (ptr->ray.pos >= ptr->ray.u_wall
			&& ptr->ray.pos <= ptr->ray.l_wall)
			put_wall(select_tex(ptr), ptr);
		else if (ptr->ray.pos > ptr->ray.l_wall && ptr->info_file.skybox)
			my_mlx_multi_put(ptr, ptr->ray.id, ptr->ray.pos,
				ptr->fov.shade[ptr->ray.pos + ratio]);
		else if (!ptr->info_file.skybox)
			my_mlx_multi_put(ptr, ptr->ray.id, ptr->ray.pos,
				ptr->fov.shade[ptr->ray.pos + ratio]);
		ptr->ray.pos++;
	}
}

static	void	distancer(float dist, t_window *ptr)
{
	int	i;
	int	x;

	i = 0;
	x = ptr->ray.id;
	while (i < ptr->fov.multi)
	{
		ptr->fov.dist[x] = dist;
		x++;
		i++;
	}
}

void	ray_cannon(float fish, t_window *ptr)
{
	float	ray_len;
	int		ray_height;
	float	ratio;

	if (ptr->input.crouch)
		ratio = 2.3;
	else
		ratio = 2;
	if (ptr->ray.dist_x < ptr->ray.dist_y && ptr->ray.dist_x != 0)
		ray_len = ptr->ray.dist_x * fish;
	else
		ray_len = ptr->ray.dist_y * fish;
	distancer(ray_len, ptr);
	ptr->fov.mod = 0 + (int)ray_len * 0.05;
	ray_height = (int)((ptr->info_file.res_y / ray_len)) + 1;
	ptr->ray.u_wall = roundf(- ((float)ray_height) / 2
			+ (float)ptr->info_file.res_y / ratio);
	ptr->ray.l_wall = roundf((float)ray_height / 2 + \
		(float)ptr->info_file.res_y / ratio);
	put_ray(ptr);
}
