/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wallcheck.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:07:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/06 15:39:24 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	inverse_cam(char dir, t_window *ptr)
{
	if (dir == 'B')
	{
		ptr->fov.vect_x *= -1;
		ptr->fov.vect_y *= -1;
	}
}

void	sprite_event(t_window *ptr, int is_heal)
{
	if (is_heal && ptr->player.health < 100)
	{
		ptr->player.health += 20;
		ptr->player.life_bar += 100;
	}
	else if (ptr->player.health > 0)
	{
		ptr->player.health -= 20;
		ptr->player.life_bar -= 100;
	}
	
}

void	sprite_inactive(t_window *ptr, int is_heal)
{
	int i;
	float player_x;
	float player_y;

	i = -1;
	player_x = ptr->player.pos_x;
	player_y = ptr->player.pos_y;
	while (ptr->sprite[++i])
	{
		if (ptr->sprite[i]->active && ft_dist(player_x, player_y, ptr->sprite[i]->x, ptr->sprite[i]->y) > 0
			&& ft_dist(player_x, player_y, ptr->sprite[i]->x, ptr->sprite[i]->y) < 0.3)
		{
			printf("Id = %i | Active = %i | Dist = %i\n",ptr->sprite[i]->id, ptr->sprite[i]->active, (int)ptr->sprite[i]->dist);
			sprite_event(ptr, is_heal);
			ptr->sprite[i]->active = 0;
			break;
		}
	}
}

int	wall_check(float x, float y, t_window *ptr)
{
	if (ptr->info_file.map[(int)y][(int)x] == '1'
		|| ptr->info_file.map[(int)y][(int)x] == '2'
		|| ptr->info_file.map[(int)y][(int)x] == '4')
		return (0);
	else if (ptr->info_file.map[(int)y][(int)x] == '5')
		sprite_inactive(ptr, 0);
	else if (ptr->info_file.map[(int)y][(int)x] == '6' )
		sprite_inactive(ptr, 1);
	return (1);
}
