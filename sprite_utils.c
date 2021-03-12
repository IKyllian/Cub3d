/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:54:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/12 12:54:52 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_swap(t_sprites **s1, t_sprites **s2)
{
	t_sprites *temp;

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
	ptr->sprite[i]->r_x = ((ptr->sprite[i]->x - ptr->player.pos_x) * ptr->fov.vect_x
		+ (ptr->sprite[i]->y - ptr->player.pos_y) * ptr->fov.vect_y)
		/ (sqrtf(powf(ptr->fov.vect_x, 2) + powf(ptr->fov.vect_y, 2))
		* (sqrtf(powf(ptr->sprite[i]->x - ptr->player.pos_x, 2)
		+ powf(ptr->sprite[i]->y - ptr->player.pos_y, 2))));
	ptr->sprite[i]->r_x = roundf((acos(ptr->sprite[i]->r_x) / 0.0174533
		* ((float)ptr->info_file.res_x / 2)) / 30);
	ptr->sprite[i]->r_x *= anglizer(ptr->fov.vect_x, ptr->fov.vect_y, ptr->sprite[i]->x - ptr->player.pos_x, ptr->sprite[i]->y - ptr->player.pos_y);
}

void	sprite_enable(t_window *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		if ((int)ptr->ray.s_y == (int)ptr->sprite[i]->y
			&& (int)ptr->ray.s_x == (int)ptr->sprite[i]->x)
			ptr->sprite[i]->visible = 1;
		i++;
	}
}

void	sprite_reset(t_window *ptr)
{
	int	i;

	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		ptr->sprite[i]->visible = 0;
		i++;
	}
}