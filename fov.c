/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:09:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/15 10:16:04 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	step_x_calc(t_window *ptr)
{
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->player.dist_x = 0;
	if (ptr->player.vect_x == 0)
		return ;
	while (s_x < ptr->info_file.map_width && s_y < ptr->info_file.map_size &&
	s_x >= 0 && s_y >= 0 && ptr->info_file.map[(int)s_y][(int)s_x] != '1')
	{
		if (ptr->player.vect_x >= 0)
			x = (int)(s_x + 1);
		else if (s_x == ptr->player.pos_x)
			x = (int)(s_x);
		else
			x = (int)(s_x - 1);
		y = s_y + ptr->player.vect_y * ((x - s_x) / ptr->player.vect_x);
		ptr->player.dist_x += sqrt(exp2(fabs(s_x - x)) + exp2(fabs(s_y - y)));
		s_x = x;
		s_y = y;
	}
	ptr->player.nwall_x = s_x;
	ptr->player.nwall_y = s_y;
}

static void	step_y_calc(t_window *ptr)
{
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->player.dist_y = 0;
	if (ptr->player.vect_y == 0)
		return ;
	while (s_x < ptr->info_file.map_width && s_y < ptr->info_file.map_size &&
	s_x >= 0 && s_y >= 0 && ptr->info_file.map[(int)s_y][(int)s_x] != '1')
	{
		if (ptr->player.vect_y >= 0)
			y = (int)(s_y + 1);
		else if (s_y == ptr->player.pos_y)
			y = (int)(s_y);
		else
			y = (int)(s_y - 1);
		x = s_x + ptr->player.vect_x * ((y - s_y) / ptr->player.vect_y);
		ptr->player.dist_y += sqrt(exp2(fabs(s_y - y)) + exp2(fabs(s_x - x)));
		s_x = x;
		s_y = y;
	}
	if (ptr->player.dist_y < ptr->player.dist_x)
		ptr->player.nwall_x = s_x;
	if (ptr->player.dist_y < ptr->player.dist_x)
		ptr->player.nwall_y = s_y;
}

void	put_rov(t_window *ptr)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	len;
	float	i;

	step_x_calc(ptr);
	step_y_calc(ptr);
	if (fabs(ptr->player.nwall_x - ptr->player.pos_x) >= fabs(ptr->player.nwall_y - ptr->player.pos_y))
		len = fabs(ptr->player.nwall_x - ptr->player.pos_x);
	else
		len = fabs(ptr->player.nwall_y - ptr->player.pos_y);
	dx = (ptr->player.nwall_x - ptr->player.pos_x) / len;
	dy = (ptr->player.nwall_y - ptr->player.pos_y) / len;
	x = ptr->player.pos_x + 0.0033;
	y = ptr->player.pos_y + 0.0033;
	i = 1;
	printf("len%f\tdistx%f\tdisty%f\ndx%f\tdy%f\n", len, ptr->player.dist_x, ptr->player.dist_y, dx, dy);
	while (i <= len && x < ptr->info_file.map_width && y < ptr->info_file.map_size && ptr->info_file.map[(int)y][(int)x] != '1')
	{
		mlx_pixel_put(ptr->mlx, ptr->win, x * ptr->ratio, y * ptr->ratio, ft_trgb(0, 255, 0, 255));
		x = x + (dx / ptr->ratio);
		y = y + (dy / ptr->ratio);
		i = i + (1 / ptr->ratio);
	}
}

void	put_fov(t_window *ptr)
{
	int		ray;
	float	cam_x;
	float	cam_y;

	ray = -30;
	cam_x = ptr->player.vect_x;
	cam_y = ptr->player.vect_y;
	while (ray <= ptr->player.fov)
	{	
		ptr->player.vect_x = cam_x * cos(0.01745 * ray) - cam_y * sin(0.01745 * ray);
		ptr->player.vect_y = cam_x * sin(0.01745 * ray) + cam_y * cos(0.01745 * ray);
		put_rov(ptr);
		ray += 1;
	}
	ptr->player.vect_x = cam_x;
	ptr->player.vect_y = cam_y;
}