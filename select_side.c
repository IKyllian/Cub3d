/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_side.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:38:43 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:11:52 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_side(t_window *ptr, int start_y, int start_x)
{
	if (ptr->info_file.map[start_y][start_x] == 'N')
		ptr->fov.vect_y = -2;
	else if (ptr->info_file.map[start_y][start_x] == 'S')
		ptr->fov.vect_y = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'E')
		ptr->fov.vect_x = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'W')
		ptr->fov.vect_x = -2;
}
