/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:49 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/24 13:44:06 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_creator(int count, int x, int y, t_window *ptr)
{
	ptr->sprite[count] = malloc(sizeof(t_sprites));
	if (!ptr->sprite[count])
		ft_error("Erreur d'allocation.", 1, ptr);
	ptr->info_file.sprite_allo_size++;
	ptr->sprite[count]->id = count;
	ptr->sprite[count]->type = 0;
	ptr->sprite[count]->visible = 0;
	ptr->sprite[count]->active = 1;
	ptr->sprite[count]->x = x + 0.5;
	ptr->sprite[count]->y = y + 0.5;
	ptr->sprite[count]->dist = sqrtf(powf(ptr->sprite[count]->x - \
			ptr->player.pos_x, 2) + powf(ptr->sprite[count]->y - \
			ptr->player.pos_y, 2));
}

void	sprite_finder(t_window *ptr)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	while (ptr->info_file.map[i])
	{
		j = 0;
		while (ptr->info_file.map[i][j])
		{
			if (ptr->info_file.map[i][j] == '2')
			{
				sprite_creator(count, j, i, ptr);
				count++;
			}
			j++;
		}
		i++;
	}
	ptr->sprite[count] = NULL;
}

void	sprite_init(t_window *ptr)
{
	t_sprites	**sprites;

	sprites = malloc(sizeof(t_sprites *) * ptr->info_file.nb_sprite + 1);
	if (!sprites)
		ft_error("Erreur d'allocation.", 1, ptr);
	ptr->sprite = sprites;
	sprite_finder(ptr);
	ptr->sp_tex = init_text_struct(ptr, ptr->info_file.t_sprite);
}
