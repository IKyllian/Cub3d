/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spriter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:06:42 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/06 14:18:28 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_sprite_pixel(int i, int x, t_texture texture, t_window *ptr)
{
	int	y;
	int	tex_x;
	int	tex_y;
	int	colour;

	y = ptr->sprite[i]->u_coord;
	while (y < ptr->sprite[i]->b_coord)
	{
		if (y >= 0 && y < ptr->info_file.res_y)
		{
			tex_x = (x - ptr->sprite[i]->l_coord) * texture.width
				/ (ptr->sprite[i]->r_coord - ptr->sprite[i]->l_coord);
			tex_y = (y - ptr->sprite[i]->u_coord) * texture.height
				/ (ptr->sprite[i]->b_coord - ptr->sprite[i]->u_coord);
			if (texture.addr[tex_y * texture.width + tex_x])
			{
				colour = trgbmod(texture.addr[tex_y * texture.width + tex_x],
					0 + (int)ptr->sprite[i]->dist * 0.05);
				my_mlx_multi_put(ptr, x, y, colour);
			}
		}
		y++;
	}
}

t_texture	select_tex_sprite(t_window *ptr, int i)
{
	if (ptr->sprite[i]->type == 4)
		return (ptr->second_sp_tex);
	else if (ptr->sprite[i]->type == 5)
		return (ptr->trap_sp_tex);
	else if (ptr->sprite[i]->type == 6)
		return (ptr->heal_sp_tex);
	return (ptr->sp_tex);
}

void	put_sprite(int i, t_texture texture, t_window *ptr)
{
	int	x;

	if (!ptr->sprite[i]->visible || !ptr->sprite[i]->active)
		return ;
	x = ptr->sprite[i]->l_coord;
	while (x < ptr->sprite[i]->r_coord)
	{
		if (x >= 0 && x < ptr->info_file.res_x && ptr->sprite[i]->dist < ptr->fov.dist[x])
			put_sprite_pixel(i, x, texture, ptr);
		x += ptr->fov.multi;
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
			sprite_disable(i, ptr);
			put_sprite(i, select_tex_sprite(ptr, i), ptr);
		}
		i++;
	}
}
