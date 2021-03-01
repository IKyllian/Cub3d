/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:58:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/23 13:45:09 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_struct_ray(t_window *ptr)
{
	t_ray ray;

	ray.id = 0;
	ray.pos = 0;
	ray.nwall_x = 0;
	ray.nwall_y = 0;
	ray.dist_x = 0;
	ray.dist_y = 0;
	ray.shift_x = 0;
	ray.shift_y = 0;
	ray.s_x = 0;
	ray.s_y = 0;
	ray.e_x = 0;
	ray.e_y = 0;
	ray.side = 0;
	ray.u_wall = 0;
	ray.l_wall = 0;
	ptr->ray = ray;
}

void		init_struct_fov(t_window *ptr)
{
	t_fov fov;

	fov.fov = 30;
	fov.vect_x = 0;
	fov.vect_y = 0;
	if (ptr->info_file.map[ptr->info_file.start_y][ptr->info_file.start_x] == 'N')
		fov.vect_y = -2;
	else if (ptr->info_file.map[ptr->info_file.start_y][ptr->info_file.start_x] == 'S')
		fov.vect_y = 2;
	else if (ptr->info_file.map[ptr->info_file.start_y][ptr->info_file.start_x] == 'E')
		fov.vect_x = 2;
	else if (ptr->info_file.map[ptr->info_file.start_y][ptr->info_file.start_x] == 'W')
		fov.vect_x = -2;
	ptr->fov = fov;
}

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
	//init_struct_fov(ptr); main.c
	init_struct_ray(ptr);
}
