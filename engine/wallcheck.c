/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcheck.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:07:11 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:11:41 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	if (is_heal)
	{
		ptr->player.health += 20;
		ptr->player.life_bar += ptr->player.life_ratio;
	}
	else
	{
		ptr->player.health -= 20;
		ptr->player.life_bar -= ptr->player.life_ratio;
	}
}

void	sprite_inactive(t_window *ptr, int is_heal, int end_sprite)
{
	int		i;
	float	pl_x;
	float	pl_y;

	i = -1;
	pl_x = ptr->player.pos_x;
	pl_y = ptr->player.pos_y;
	while (ptr->sprite[++i])
	{
		if (ptr->sprite[i]->active
			&& ft_dist(pl_x, pl_y, ptr->sprite[i]->x, ptr->sprite[i]->y) > 0
			&& ft_dist(pl_x, pl_y, ptr->sprite[i]->x, ptr->sprite[i]->y) < 0.4)
		{
			if (end_sprite)
				ft_error("Bravo vous avez trouvé Chopper !", 2, ptr, 0);
			else if ((is_heal && ptr->player.health < 100)
				|| (ptr->player.health > 0 && !is_heal))
			{
				sprite_event(ptr, is_heal);
				ptr->sprite[i]->active = 0;
			}
			break ;
		}
	}
}

int	wall_check(float x, float y, t_window *ptr)
{
	if (ptr->info_file.map[(int)y][(int)x] == '1'
		|| ptr->info_file.map[(int)y][(int)x] == '2')
		return (0);
	else if (ptr->info_file.map[(int)y][(int)x] == '4')
		sprite_inactive(ptr, 0, 1);
	else if (ptr->info_file.map[(int)y][(int)x] == '5')
		sprite_inactive(ptr, 0, 0);
	else if (ptr->info_file.map[(int)y][(int)x] == '6' )
		sprite_inactive(ptr, 1, 0);
	return (1);
}
