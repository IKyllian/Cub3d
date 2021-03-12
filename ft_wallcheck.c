/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:07:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/12 11:05:56 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	tan_x_calc(t_window *ptr)
{
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->ray.dist_x = 0;
	while (s_x < ptr->info_file.map_width && s_y < ptr->info_file.map_size &&
	s_x >= 0 && s_y >= 0 && ptr->info_file.map[(int)s_y][(int)s_x] != '1')
	{
		if (ptr->fov.vect_x >= 0)
			x = (int)(s_x + 1);
		else if (s_x == ptr->player.pos_y)
			x = (int)(s_x);
		else
			x = (int)(s_x - 1);
		y = s_y + ptr->fov.vect_y * ((x - s_x) / ptr->fov.vect_x);
		ptr->ray.dist_x += sqrt(powf(s_x - x, 2) + powf(s_y - y, 2));
		s_x = x;
		s_y = y;
	}
	ptr->ray.nwall_x = s_x;
	ptr->ray.nwall_y = s_y;
}


static void	tan_y_calc(t_window *ptr)
{
	float	s_x;
	float	s_y;
	float	x;
	float	y;

	s_x = ptr->player.pos_x;
	s_y = ptr->player.pos_y;
	ptr->ray.dist_x = 0;
	while (s_x < ptr->info_file.map_width && s_y < ptr->info_file.map_size &&
	s_x >= 0 && s_y >= 0 && ptr->info_file.map[(int)s_y][(int)s_x] != '1')
	{
		if (ptr->fov.vect_y >= 0)
			y = (int)(s_y + 1);
		else if (s_y == ptr->player.pos_x)
			y = (int)(s_y);
		else
			y = (int)(s_y - 1);
		x = s_x + ptr->fov.vect_x * ((y - s_y) / ptr->fov.vect_y);
		ptr->ray.dist_y += sqrt(powf(s_y - y, 2) + powf(s_x - x, 2));
		s_x = x;
		s_y = y;
	}
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_x = s_x;
	if (ptr->ray.dist_y < ptr->ray.dist_x)
		ptr->ray.nwall_y = s_y;
}

void	inverse_cam(char dir, t_window *ptr)
{
	if (dir == 'B')
	{
		ptr->fov.vect_x *= -1;
		ptr->fov.vect_y *= -1;
	}
}

void	wall_dist_calc(char dir, t_window *ptr)
{
	inverse_cam(dir, ptr);
	tan_x_calc(ptr);
	tan_y_calc(ptr);
	inverse_cam(dir, ptr);
}

int		wall_check(float x, float y, t_window *ptr)
{
	int c_x;
	int c_y;

	c_x = (int)x;
	c_y = (int)y;
	if ((ptr->fov.vect_y >= 0 && ptr->fov.vect_y <= 0)
	&& ((x >= ptr->ray.nwall_x && y <= ptr->ray.nwall_y)
	|| (ptr->info_file.map[c_y][c_x] == '1')))
		return (0);
	else if ((ptr->fov.vect_y >= 0 && ptr->fov.vect_y >= 0)
	&& ((x >= ptr->ray.nwall_x && y >= ptr->ray.nwall_y)
	|| (ptr->info_file.map[c_y][c_x] == '1')))
		return (0);
	else if ((ptr->fov.vect_y <= 0 && ptr->fov.vect_y >= 0)
	&& ((x <= ptr->ray.nwall_x && y >= ptr->ray.nwall_y)
	|| (ptr->info_file.map[c_y][c_x] == '1')))
		return (0);
	else if ((ptr->fov.vect_y <= 0 && ptr->fov.vect_y <= 0)
	&& ((x <= ptr->ray.nwall_x && y <= ptr->ray.nwall_y)
	|| (ptr->info_file.map[c_y][c_x] == '1')))
		return (0);
	return (1);
}