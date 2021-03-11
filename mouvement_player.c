/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/10 10:37:59 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		pl_move(int keycode, t_window *ptr)
{
	float x;
	float y;
	
	x = ptr->player.pos_x;
	y = ptr->player.pos_y;
	if ((keycode == 13 || keycode == 126) && !is_collision('F', ptr)) // Touche w et fleche haut
	{
		ptr->player.pos_x = x + ptr->fov.vect_x * 0.1;
		ptr->player.pos_y = y + ptr->fov.vect_y * 0.1;
	}
	else if ((keycode == 1 || keycode == 125) && !is_collision('B', ptr)) // Touche s et fleche bas
	{
		ptr->player.pos_x = x - ptr->fov.vect_x * 0.1;
		ptr->player.pos_y = y - ptr->fov.vect_y * 0.1;
	}
	return (0);
}

int	pl_rotation(int keycode, t_window *ptr)
{
	float vect_x;
	float vect_y;

	vect_x = ptr->fov.vect_x;
	vect_y = ptr->fov.vect_y;
	if ((keycode == 2 || keycode == 124)) //d et fleche droite
	{
		ptr->fov.vect_x = vect_x * cos(0.1) - vect_y * sin(0.1);
		ptr->fov.vect_y = vect_x * sin(0.1) + vect_y * cos(0.1);
	}
	else if ((keycode == 0 || keycode == 123)) // a et fleche gauche
	{
		ptr->fov.vect_x = vect_x * cos(-0.1) - vect_y * sin(-0.1);
		ptr->fov.vect_y = vect_x * sin(-0.1) + vect_y * cos(-0.1);
	}
	return (0);
}

int	key_move(int keycode, t_window *ptr)
{
	int vect_x;
	int vect_y;
	int ratio;

	sprite_reset(ptr);
	ratio = ptr->ratio;
	vect_x = (ptr->player.pos_x +  ptr->fov.vect_x) * ratio;
	vect_y = (ptr->player.pos_y + ptr->fov.vect_y) * ratio;
	if (keycode == 126 || keycode == 13 || keycode == 125 || keycode == 1)
		pl_move(keycode, ptr);
	else if (keycode == 0 || keycode == 2 || keycode == 124 || keycode == 123)
		pl_rotation(keycode, ptr);
	sprite_dist(ptr);
	return (0);
}

int is_collision(char dir, t_window *ptr)
{
	float	x;
	float	y;

	wall_dist_calc(dir, ptr);
	if (dir == 'F')
	{
		x = ptr->player.pos_x + ptr->fov.vect_x * 0.1;
		y =  ptr->player.pos_y + ptr->fov.vect_y * 0.1;
		if (!wall_check(x, y, ptr))
			return (1);
		return (0);
	}
	else if (dir == 'B')
	{
		x = ptr->player.pos_x - ptr->fov.vect_x * 0.1;
		y =  ptr->player.pos_y - ptr->fov.vect_y * 0.1;
		inverse_cam('B', ptr);
		if (!wall_check(x, y, ptr))
		{
			inverse_cam('B', ptr);	
			return (1);
		}
		inverse_cam('B', ptr);
		return (0);
	}
	return (0);
}