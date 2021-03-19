/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 13:59:31 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sprite(int i, t_texture texture, t_window *ptr)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	
	if (!ptr->sprite[i]->visible)
		return ;
	x = ptr->sprite[i]->l_coord;
	while (x < ptr->sprite[i]->r_coord)
	{
		if (x >= 0 && x < ptr->info_file.res_x && ptr->sprite[i]->dist < ptr->fov.dist[x])
		{
			y = ptr->sprite[i]->u_coord;
			while (y < ptr->sprite[i]->b_coord)
			{
				if (y >= 0 && y < ptr->info_file.res_y)
				{
					tex_x = (x - ptr->sprite[i]->l_coord) * texture.width / (ptr->sprite[i]->r_coord - ptr->sprite[i]->l_coord);
					tex_y = (y - ptr->sprite[i]->u_coord) * texture.height
						/ (ptr->sprite[i]->b_coord - ptr->sprite[i]->u_coord);
					if (texture.addr[tex_y * texture.width + tex_x])
					{
						my_mlx_pixel_put(ptr, x, y,
							texture.addr[tex_y * texture.width + tex_x]);
					}
				}
				y++;
			}
		}
		x++;
	}
}

void	sprite_check(t_window *ptr)
{
	int	i;

	sprite_sort(ptr);
	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		if (ptr->sprite[i]->dist > 0.1)
		{
			sprite_xpos(i, ptr);
			sprite_sizer(i, ptr);
			// sprite_enable(i, mlx);
			put_sprite(i, ptr->sp_tex, ptr);
		}
		i++;
	}
}
