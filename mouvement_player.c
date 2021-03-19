/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 14:29:44 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pl_move(int keycode, t_window *ptr, float speed)
{
	if (keycode == 13 && !is_collision('F', ptr, speed)) // Touche w et fleche haut
	{
		ptr->player.pos_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
		ptr->player.pos_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
	}
	else if (keycode == 1 && !is_collision('B', ptr, speed)) // Touche s et fleche bas
	{
		ptr->player.pos_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
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
	if (keycode == 124) //d et fleche droite
	{
		ptr->fov.vect_x = vect_x * cos(speed) - vect_y * sin(speed);
		ptr->fov.vect_y = vect_x * sin(speed) + vect_y * cos(speed);
	}
	else if (keycode == 123) // a et fleche gauche
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
	if (keycode == 0 && !is_collision('F', ptr, speed))
	{
		ptr->player.pos_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
		ptr->player.pos_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
	}
	else if (keycode == 2 && !is_collision('B', ptr, speed))
	{
		ptr->player.pos_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
		ptr->player.pos_y = ptr->player.pos_y - ptr->fov.vect_y * speed;
	}
	ptr->fov.vect_x = vec_x;
	ptr->fov.vect_y = vec_y;
	return (0);
}

int	key_move(t_window *ptr)
{
	float speed;

	if ((ptr->input.forward || ptr->input.backward)
		&& (ptr->input.strafe_l || ptr->input.strafe_r))
		speed = 0.025;
	else
		speed = 0.025;
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
	sprite_dist(ptr);
	return (0);
}

int	is_collision(char dir, t_window *ptr, float speed)
{
	wall_dist_calc(dir, ptr);
	if (dir == 'F')
	{
		ptr->player.f_x = ptr->player.pos_x + ptr->fov.vect_x * speed;
		ptr->player.f_y = ptr->player.pos_y + ptr->fov.vect_y * speed;
		if (!wall_check(ptr->player.f_x, ptr->player.f_y, ptr))
		{
			return (1);
		}
		return (0);
	}
	else if (dir == 'B')
	{
		ptr->player.f_x = ptr->player.pos_x - ptr->fov.vect_x * speed;
		ptr->player.f_y = ptr->player.pos_y - ptr->fov.vect_y * speed;
		inverse_cam('B', ptr);
		if (!wall_check(ptr->player.f_x, ptr->player.f_y, ptr))
		{
			inverse_cam('B', ptr);
			return (1);
		}
		inverse_cam('B', ptr);
		return (0);
	}
	return (0);
}
