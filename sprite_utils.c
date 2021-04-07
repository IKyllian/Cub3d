/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:54:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 14:49:25 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_swap(t_sprites **s1, t_sprites **s2)
{
	t_sprites	*temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sprite_sort(t_window *ptr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		j = i + 1;
		while (j < ptr->info_file.nb_sprite)
		{
			if (ptr->sprite[i]->dist < ptr->sprite[j]->dist)
				sprite_swap(&ptr->sprite[i], &ptr->sprite[j]);
			j++;
		}
		i++;
	}
}

void	sprite_xpos(int i, t_window *ptr)
{
	ptr->sprite[i]->d_x = ptr->sprite[i]->x - ptr->player.pos_x;
	ptr->sprite[i]->d_y = ptr->sprite[i]->y - ptr->player.pos_y;
	ptr->sprite[i]->r_x = (ptr->sprite[i]->d_x * ptr->fov.vect_x
			+ ptr->sprite[i]->d_y * ptr->fov.vect_y)
		/ (dist_calc(ptr->fov.vect_x, ptr->fov.vect_y)
			* (dist_calc(ptr->sprite[i]->d_x, ptr->sprite[i]->d_y)));
	if (ptr->sprite[i]->r_x > 1)
		ptr->sprite[i]->r_x = 1;
	else if (ptr->sprite[i]->r_x < -1)
		ptr->sprite[i]->r_x = -1;
	ptr->sprite[i]->angle = acos(ptr->sprite[i]->r_x);
	ptr->sprite[i]->r_x = roundf((tan(acos(ptr->sprite[i]->r_x))
				* ((float)ptr->info_file.res_x / 2)) / \
				tan(deg_rad(ptr->fov.fov)));
	ptr->sprite[i]->r_x *= anglizer(ptr->fov.vect_x, ptr->fov.vect_y,
			ptr->sprite[i]->d_x, ptr->sprite[i]->d_y);
}

void	sprite_reset(t_window *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		ptr->sprite[i]->visible = 1;
		i++;
	}
}
