/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement_player2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:37:39 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 14:43:49 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	relocate(t_window *ptr)
{
	if (ptr->info_file.map[(int)ptr->player.pos_y] \
		[(int)ptr->player.pos_x + 1] == '1'
		&& ptr->player.pos_x > (int)ptr->player.pos_x + 0.9)
		ptr->player.pos_x = (int)ptr->player.pos_x + 0.9;
	else if (ptr->info_file.map[(int)ptr->player.pos_y] \
		[(int)ptr->player.pos_x - 1] == '1'
		&& ptr->player.pos_x < (int)ptr->player.pos_x + 0.1)
		ptr->player.pos_x = (int)ptr->player.pos_x + 0.1;
	if (ptr->info_file.map[(int)ptr->player.pos_y + 1] \
		[(int)ptr->player.pos_x] == '1'
		&& ptr->player.pos_y > (int)ptr->player.pos_y + 0.9)
		ptr->player.pos_y = (int)ptr->player.pos_y + 0.9;
	else if (ptr->info_file.map[(int)ptr->player.pos_y - 1] \
		[(int)ptr->player.pos_x] == '1'
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
