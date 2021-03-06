/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:09:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/10 12:49:15 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	shift_init(t_window *ptr)
{
	if (ptr->fov.vect_x >= 0)
		ptr->ray.shift_x = 0;
	else
		ptr->ray.shift_x = 1;
	if (ptr->fov.vect_y >= 0)
		ptr->ray.shift_y = 0;
	else
		ptr->ray.shift_y = 1;
}

static void	step_x_calc(t_window *ptr)
{
	ptr->ray.s_x = ptr->player.pos_x;
	ptr->ray.s_y = ptr->player.pos_y;
	ptr->ray.dist_x = 0;
	if (ptr->fov.vect_x == 0)
		return ;
	find_y(ptr);
	while (is_valid_coord(ptr->ray.shift_x, 0, ptr))
	{
		ptr->ray.s_x += ptr->ray.n_x;
		ptr->ray.s_y += ptr->ray.n_y;
	}
	ptr->ray.dist_x = ft_dist(ptr->ray.s_x, ptr->ray.s_y,
			ptr->player.pos_x, ptr->player.pos_y);
	ptr->ray.nwall_x = ptr->ray.s_x;
	ptr->ray.nwall_y = ptr->ray.s_y;
}

static void	step_y_calc(t_window *ptr)
{
	ptr->ray.s_x = ptr->player.pos_x;
	ptr->ray.s_y = ptr->player.pos_y;
	ptr->ray.dist_y = 0;
	if (ptr->fov.vect_y == 0)
		return ;
	find_x(ptr);
	while (is_valid_coord(0, ptr->ray.shift_y, ptr))
	{
		ptr->ray.s_x += ptr->ray.n_x;
		ptr->ray.s_y += ptr->ray.n_y;
	}
	ptr->ray.dist_y = ft_dist(ptr->ray.s_x, ptr->ray.s_y,
			ptr->player.pos_x, ptr->player.pos_y);
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_x = ptr->ray.s_x;
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_y = ptr->ray.s_y;
}

void	put_rov(float fish, t_window *ptr)
{
	shift_init(ptr);
	step_x_calc(ptr);
	step_y_calc(ptr);
	ray_cannon(fish, ptr);
}

void	put_fov(t_window *ptr)
{
	float	ray;
	float	nb_ray;
	float	cam_x;
	float	cam_y;

	ray = -ptr->fov.fov;
	nb_ray = ((float)ptr->fov.fov * 2) / ((float)ptr->info_file.res_x);
	cam_x = ptr->fov.vect_x;
	cam_y = ptr->fov.vect_y;
	ptr->ray.id = 0;
	while (ray <= ptr->fov.fov && ptr->ray.id < ptr->info_file.res_x)
	{	
		ptr->fov.vect_x = cam_x * cos(0.01745 * ray) - \
			cam_y * sin(0.01745 * ray);
		ptr->fov.vect_y = cam_x * sin(0.01745 * ray) + \
			cam_y * cos(0.01745 * ray);
		put_rov(cos(0.01745 * ray), ptr);
		ray += nb_ray * ptr->fov.multi;
		ptr->ray.id += ptr->fov.multi;
	}
	ptr->fov.vect_x = cam_x;
	ptr->fov.vect_y = cam_y;
}
