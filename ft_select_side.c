/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select_side.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 13:38:43 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 13:38:59 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	select_side(t_window *ptr, t_fov *fov, int start_y, int start_x)
{
	if (ptr->info_file.map[start_y][start_x] == 'N')
		fov->vect_y = -2;
	else if (ptr->info_file.map[start_y][start_x] == 'S')
		fov->vect_y = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'E')
		fov->vect_x = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'W')
		fov->vect_x = -2;
}
