/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:47:32 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/01 11:33:29 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int keycode, t_window *ptr)
{
	if (keycode == 53)
		ft_error("\0", 0, ptr);
	if (keycode == 13)
		ptr->input.forward = 1;
	if (keycode == 1)
		ptr->input.backward = 1;
	if (keycode == 123)
		ptr->input.rotate_l = 1;
	if (keycode == 124)
		ptr->input.rotate_r = 1;
	if (keycode == 0)
		ptr->input.strafe_l = 1;
	if (keycode == 2)
		ptr->input.strafe_r = 1;
	if (keycode == 257)
		ptr->input.crouch = 1;
	return (0);
}

int	key_release(int keycode, t_window *ptr)
{
	if (keycode == 13)
		ptr->input.forward = 0;
	if (keycode == 1)
		ptr->input.backward = 0;
	if (keycode == 123)
		ptr->input.rotate_l = 0;
	if (keycode == 124)
		ptr->input.rotate_r = 0;
	if (keycode == 0)
		ptr->input.strafe_l = 0;
	if (keycode == 2)
		ptr->input.strafe_r = 0;
	if (keycode == 257)
		ptr->input.crouch = 0;
	return (0);
}

void	input_init(t_window *ptr)
{
	t_input	input;

	input.backward = 0;
	input.forward = 0;
	input.rotate_l = 0;
	input.rotate_r = 0;
	input.strafe_l = 0;
	input.strafe_r = 0;
	input.crouch = 0;
	ptr->input = input;
}
