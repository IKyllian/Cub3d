/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:09:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/23 13:57:07 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->ray.dist_x = 0;
	if (ptr->fov.vect_x == 0)
		return ;
	while (1)
	{
		if (ptr->fov.vect_x >= 0)
			x = (int)(s_x + 1);
		else if (s_x == ptr->player.pos_x)
			x = (int)(s_x);
		else
			x = (int)(s_x - 1);
		y = s_y + ptr->fov.vect_y * ((x - s_x) / ptr->fov.vect_x);
		s_x = x;
		s_y = y;
		if (s_x >= ptr->info_file.map_width || s_y >= ptr->info_file.map_size ||
		s_x - ptr->ray.shift_x < 0 || s_y < 0 || ptr->info_file.map[(int)s_y][(int)s_x - ptr->ray.shift_x] == '1')
			break ;
	}
	ptr->ray.dist_x = sqrtf(powf(ptr->player.pos_x - s_x, 2) + powf(ptr->player.pos_y - s_y, 2));
	ptr->ray.nwall_x = s_x;
	ptr->ray.nwall_y = s_y;
}

static void	step_y_calc(t_window *ptr)
{
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->ray.dist_y = 0;
	if (ptr->fov.vect_y == 0)
		return ;
	while (1)
	{
		if (ptr->fov.vect_y >= 0)
			y = (int)(s_y + 1);
		else if (s_y == ptr->player.pos_y)
			y = (int)(s_y);
		else
			y = (int)(s_y - 1);
		x = s_x + ptr->fov.vect_x * ((y - s_y) / ptr->fov.vect_y);
		s_x = x;
		s_y = y;
		if (s_x >= ptr->info_file.map_width || s_y >= ptr->info_file.map_size ||
		s_x < 0 || s_y - ptr->ray.shift_y < 0 || ptr->info_file.map[(int)s_y - ptr->ray.shift_y][(int)s_x] == '1')
			break ;
	}
	ptr->ray.dist_y = sqrtf(powf(ptr->player.pos_x - s_x, 2) + powf(ptr->player.pos_y - s_y, 2));
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_x = s_x;
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_y = s_y;
}

void	put_rov(float fish, t_window *ptr)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	len;
	float	i;

	shift_init(ptr);
	step_x_calc(ptr);
	step_y_calc(ptr);
	if (fabs(ptr->ray.nwall_x - ptr->player.pos_x) >= fabs(ptr->ray.nwall_y - ptr->player.pos_y))
		len = fabs(ptr->ray.nwall_x - ptr->player.pos_x);
	else
		len = fabs(ptr->ray.nwall_y - ptr->player.pos_y);
	dx = (ptr->ray.nwall_x - ptr->player.pos_x) / len;
	dy = (ptr->ray.nwall_y - ptr->player.pos_y) / len;
	x = ptr->player.pos_x + 0.0033;
	y = ptr->player.pos_y + 0.0033;
	i = 1;
	while (i <= len && x < ptr->info_file.map_width && y < ptr->info_file.map_size && ptr->info_file.map[(int)y][(int)x] != '1')
	{
		//my_mlx_pixel_put(ptr, x * ptr->ratio, y * ptr->ratio, ft_trgb(0, 255, 0, 255));
		x = x + (dx / ptr->ratio);
		y = y + (dy / ptr->ratio);
		i = i + (1 / ptr->ratio);
	}
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
		ptr->fov.vect_x = cam_x * cos(0.01745 * ray) - cam_y * sin(0.01745 * ray);
		ptr->fov.vect_y = cam_x * sin(0.01745 * ray) + cam_y * cos(0.01745 * ray);
		put_rov(cos(0.01745*ray), ptr);
		ray += nb_ray;
		ptr->ray.id++;
	}
	ptr->fov.vect_x = cam_x;
	ptr->fov.vect_y = cam_y;
}