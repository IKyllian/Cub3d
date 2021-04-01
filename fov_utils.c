/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:21:38 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/31 16:25:51 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	step_init(float cam, float start, float pl)
{
	if (cam >= 0)
		return ((int)start + 1);
	else if (start == pl)
		return ((int)start);
	else
		return ((int)start - 1);
}

void	find_y(t_window *ptr)
{
	float	temp;

	if (ptr->fov.vect_x >= 0)
	{
		ptr->ray.n_x = 1;
		ptr->ray.s_x = (int)ptr->ray.s_x + 1;
	}
	else if (ptr->ray.s_x == ptr->player.pos_x)
	{
		ptr->ray.n_x = 0;
		ptr->ray.s_x = (int)ptr->ray.s_x;
	}
	else
	{
		ptr->ray.n_x = -1;
		ptr->ray.s_x = (int)ptr->ray.s_x - 1;
	}
	ptr->ray.s_y = ptr->player.pos_y + ptr->fov.vect_y
		* ((ptr->ray.s_x - ptr->player.pos_x) / ptr->fov.vect_x);
	if (ptr->ray.n_x == 0)
		ptr->ray.n_x -= 1;
	temp = ptr->ray.s_y + ptr->fov.vect_y * ((ptr->ray.n_x) / ptr->fov.vect_x);
	ptr->ray.n_y = temp - ptr->ray.s_y;
}

void	find_x(t_window *ptr)
{
	float	temp;

	if (ptr->fov.vect_y >= 0)
	{
		ptr->ray.n_y = 1;
		ptr->ray.s_y = (int)ptr->ray.s_y + 1;
	}
	else if (ptr->ray.s_y == ptr->player.pos_y)
	{
		ptr->ray.n_y = 0;
		ptr->ray.s_y = (int)ptr->ray.s_y;
	}
	else
	{
		ptr->ray.n_y = -1;
		ptr->ray.s_y = (int)ptr->ray.s_y - 1;
	}
	ptr->ray.s_x = ptr->player.pos_x + ptr->fov.vect_x
		* ((ptr->ray.s_y - ptr->player.pos_y) / ptr->fov.vect_y);
	if (ptr->ray.n_y == 0)
		ptr->ray.n_y -= 1;
	temp = ptr->ray.s_x + ptr->fov.vect_x * ((ptr->ray.n_y) / ptr->fov.vect_y);
	ptr->ray.n_x = temp - ptr->ray.s_x;
}

int	is_valid_coord(float x, float y, int shft_x, int shft_y, t_window *ptr)
{
	if (x >= ptr->info_file.map_width || y >= ptr->info_file.map_size
		|| x - shft_x < 0 || y - shft_y < 0
		|| ptr->info_file.map[(int)y - shft_y]
		[(int)x - shft_x] == '1' || ptr->info_file.map[(int)y - shft_y]
		[(int)x - shft_x] == '3')
		return (0);
	return (1);
}
