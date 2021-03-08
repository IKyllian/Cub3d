/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/08 11:06:44 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	swap_sprite(t_sprites **s1, t_sprites **s2)
{
	t_sprites *temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sort_sprite(t_window *ptr)
{
	int 		i;
	int			j;

	i = -1;
	// printf("posx = %f | posy = %f\n", ptr->sprite[0]->x, ptr->sprite[0]->y);
	// printf("posx2 = %f | posy2 = %f\n", ptr->sprite[1]->x, ptr->sprite[1]->y);
	while (ptr->sprite[++i])
	{
		j = i + 1;
		while (j < ptr->info_file.nb_sprite && ptr->sprite[j])
		{
			if (sqrtf(powf(ptr->player.pos_x - ptr->sprite[i]->x, 2)
			+ powf(ptr->player.pos_y - ptr->sprite[i]->y, 2)) > sqrtf(powf(ptr->player.pos_x - ptr->sprite[j]->x, 2)
			+ powf(ptr->player.pos_y - ptr->sprite[j]->y, 2)))
			{
				//printf("Condition\n");
			}
			j++;
		}
	}
}

void	put_sprite(t_texture texture, t_window *ptr)
{
	int	tex_x;
	int	tex_y;

	tex_x = fmodf(ptr->ray.nwall_x, 1) * texture.width;
	if (fmodf(ptr->ray.nwall_x, 1) == 0)
		tex_x = fmodf(ptr->ray.nwall_y, 1) * texture.width;
	tex_y = (ptr->ray.pos - ptr->ray.u_wall) * texture.height
		/ (ptr->ray.l_wall - ptr->ray.u_wall);
	if (tex_y > texture.height - 1)
		tex_y -= 1;
	// my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
	// texture.addr[tex_y * texture.width + tex_x]);
}

void	sprite_check(t_window *ptr)
{
	sort_sprite(ptr);
	put_sprite(ptr->sp_tex, ptr);
}
