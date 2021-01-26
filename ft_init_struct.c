/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:58:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/26 16:12:57 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_file(t_info_file *elem_f)
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
	elem_f->map_size = 0;
	elem_f->map_index = -1;
	//elem_f->file = NULL;
	//elem_f->cpy_map = NULL;
}

void	init_struct_player(t_player *player)
{
	player->pos_x = 0;
	player->pos_y = 0;
}

void	init_struct_ptr(t_window *ptr)
{
	t_player 	player;
	t_info_file info_file;

	init_struct_player(&player);
	init_struct_file(&info_file);
	ptr->win = NULL;
	ptr->mlx = NULL;
	ptr->is_press = 0;
	ptr->info_file = info_file;
	ptr->player = player;
}
