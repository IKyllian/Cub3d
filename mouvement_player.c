/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/01 10:55:42 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	relocate(t_window *ptr)
{
	if (ptr->info_file.map[(int)ptr->player.pos_y][(int)ptr->player.pos_x + 1] == '1'
		&& ptr->player.pos_x > (int)ptr->player.pos_x + 0.9)
		ptr->player.pos_x = (int)ptr->player.pos_x + 0.9;
	else if (ptr->info_file.map[(int)ptr->player.pos_y][(int)ptr->player.pos_x - 1] == '1'
		&& ptr->player.pos_x < (int)ptr->player.pos_x + 0.1)
		ptr->player.pos_x = (int)ptr->player.pos_x + 0.1;
	if (ptr->info_file.map[(int)ptr->player.pos_y + 1][(int)ptr->player.pos_x] == '1'
		&& ptr->player.pos_y > (int)ptr->player.pos_y + 0.9)
		ptr->player.pos_y = (int)ptr->player.pos_y + 0.9;
	else if (ptr->info_file.map[(int)ptr->player.pos_y - 1][(int)ptr->player.pos_x] == '1'
		&& ptr->player.pos_y < (int)ptr->player.pos_y + 0.1)
		ptr->player.pos_y = (int)ptr->player.pos_y + 0.1;
}

int	check_f_coords(char side, t_window *ptr, float speed)
{
	ptr->player.f_x = ptr->player.pos_x;
	ptr->player.f_y = ptr->player.pos_y;
	if (side == 'x')
		ptr->player.f_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
	else if (side == 'y')
		ptr->player.f_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
	if (!wall_check(ptr->player.f_x, ptr->player.f_y, ptr))
		return (0);
	return (1);
}

int	check_b_coords(char side, t_window *ptr, float speed)
{
	ptr->player.f_x = ptr->player.pos_x;
	ptr->player.f_y = ptr->player.pos_y;
	if (side == 'x')
		ptr->player.f_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
	else if (side == 'y')
		ptr->player.f_y = ptr->player.pos_y - ptr->fov.vect_y * speed;
	inverse_cam('B', ptr);
	if (!wall_check(ptr->player.f_x, ptr->player.f_y, ptr))
	{
		inverse_cam('B', ptr);
		return (0);
	}
	inverse_cam('B', ptr);
	return (1);
}

int	pl_move(int keycode, t_window *ptr, float speed)
{
	if (keycode == 13)
	{
		if (check_f_coords('x', ptr, speed))
			ptr->player.pos_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
		if (check_f_coords('y', ptr, speed))
			ptr->player.pos_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
	}
	else if (keycode == 1)
	{
		if (check_b_coords('x', ptr, speed))
			ptr->player.pos_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
		if (check_b_coords('y', ptr, speed))
			ptr->player.pos_y = ptr->player.pos_y - ptr->fov.vect_y * speed;
	}
	return (0);
}

int	pl_rotation(int keycode, t_window *ptr, float speed)
{
	float	vect_x;
	float	vect_y;

	vect_x = ptr->fov.vect_x;
	vect_y = ptr->fov.vect_y;
	if (keycode == 124)
	{
		ptr->fov.vect_x = vect_x * cos(speed) - vect_y * sin(speed);
		ptr->fov.vect_y = vect_x * sin(speed) + vect_y * cos(speed);
	}
	else if (keycode == 123)
	{
		ptr->fov.vect_x = vect_x * cos(-speed) - vect_y * sin(-speed);
		ptr->fov.vect_y = vect_x * sin(-speed) + vect_y * cos(-speed);
	}
	return (0);
}

int	pl_strafe(int keycode, t_window *ptr, float speed)
{
	float	vec_x;
	float	vec_y;

	vec_x = ptr->fov.vect_x;
	vec_y = ptr->fov.vect_y;
	ptr->fov.vect_x = vec_x * cos(-1.5708) - vec_y * sin(-1.5708);
	ptr->fov.vect_y = vec_x * sin(-1.5708) + vec_y * cos(-1.5708);
	if (keycode == 0)
	{
		if (check_f_coords('x', ptr, speed))
			ptr->player.pos_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
		if (check_f_coords('y', ptr, speed))
			ptr->player.pos_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
	}
	else if (keycode == 2)
	{
		if (check_b_coords('x', ptr, speed))
			ptr->player.pos_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
		if (check_b_coords('y', ptr, speed))
			ptr->player.pos_y = ptr->player.pos_y - ptr->fov.vect_y * speed;
	}
	ptr->fov.vect_x = vec_x;
	ptr->fov.vect_y = vec_y;
	return (0);
}

int	key_move(t_window *ptr)
{
	float	speed;

	if (ptr->input.crouch)
		speed = 0.020;
	else if ((ptr->input.forward || ptr->input.backward)
		&& (ptr->input.strafe_l || ptr->input.strafe_r) && !ptr->input.crouch)
		speed = 0.025;
	else
	 	speed = 0.050;
	if (ptr->input.forward && !ptr->input.backward)
		pl_move(13, ptr, speed);
	else if (ptr->input.backward && !ptr->input.forward)
		pl_move(1, ptr, speed);
	if (ptr->input.strafe_l && !ptr->input.strafe_r)
		pl_strafe(0, ptr, speed);
	else if (ptr->input.strafe_r && !ptr->input.strafe_l)
		pl_strafe(2, ptr, speed);
	if (ptr->input.rotate_l && !ptr->input.rotate_r)
		pl_rotation(123, ptr, speed);
	else if (ptr->input.rotate_r && !ptr->input.rotate_l)
		pl_rotation(124, ptr, speed);
	if (ptr->input.crouch)
		pl_move(125, ptr, speed);
	relocate(ptr);
	sprite_dist(ptr);
	return (0);
}
