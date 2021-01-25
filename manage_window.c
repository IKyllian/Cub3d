/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:50:53 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/25 12:59:50 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int keycode, t_window *ptr)
{
	(void)ptr;
	if (keycode == 53)
		exit(0);
	return (0);
}