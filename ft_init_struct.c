/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:58:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/15 10:22:18 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_struct_file(t_info_file *elem_f)
{
	elem_f->res_x = -1;
	elem_f->res_y = -1;
	elem_f->t_no = NULL;
	elem_f->t_so = NULL;
	elem_f->t_we = NULL;
	elem_f->t_ea = NULL;
	elem_f->sprite = NULL;
	elem_f->ground = -1;
	elem_f->ceiling = -1;
	elem_f->start_x = -1;
	elem_f->start_y = -1;
	elem_f->map_width = 0;
	elem_f->map_size = 0;
	elem_f->map_index = -1;
	//elem_f->file = NULL;
	//elem_f->cpy_map = NULL;
}

t_player	init_struct_player(t_window *ptr)
{
	t_player	player;

	player.pos_x = 0;
	player.pos_y = 0;
	player.pos_x = ptr->info_file.start_x + 0.5;
	player.pos_y = ptr->info_file.start_y + 0.5;
	player.vect_y = -2;
	player.vect_x = 0;
	player.fov = 30;
	player.cam_len = (tan(player.fov / 2) * 2) * 2;
	player.len_per_ray = player.cam_len / (player.fov * 2);
	return (player);
}

void		init_struct_ptr(t_window *ptr)
{
	t_info_file info_file;

	init_struct_file(&info_file);
	ptr->win = NULL;
	ptr->mlx = NULL;
	ptr->img = NULL;
	ptr->is_press = 0;
	ptr->ratio = 10;
	ptr->info_file = info_file;
}
