/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:58:16 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 14:52:18 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_struct_ray(t_window *ptr)
{
	t_ray	ray;

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
	ray.n_x = 0;
	ray.n_y = 0;
	ray.side = 0;
	ray.u_wall = 0;
	ray.l_wall = 0;
	ptr->ray = ray;
}

void	init_struct_fov(t_window *ptr)
{
	t_fov	fov;
	int		start_y;
	int		start_x;

	start_y = ptr->info_file.start_y;
	start_x = ptr->info_file.start_x;
	fov.fov = 30;
	fov.vect_x = 0;
	fov.vect_y = 0;
	if (ptr->info_file.map[start_y][start_x] == 'N')
		fov.vect_y = -2;
	else if (ptr->info_file.map[start_y][start_x] == 'S')
		fov.vect_y = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'E')
		fov.vect_x = 2;
	else if (ptr->info_file.map[start_y][start_x] == 'W')
		fov.vect_x = -2;
	fov.dist = malloc(sizeof(float) * ptr->info_file.res_x);
	if (!fov.dist)
		ft_error(4, ptr);
	ptr->fov = fov;
	pl_rotation(123, ptr, 0.05);
	pl_rotation(124, ptr, 0.05);
}

void	init_struct_file(t_info_file *elem_f)
{
	elem_f->res_x = -1;
	elem_f->res_y = -1;
	elem_f->t_no = NULL;
	elem_f->t_so = NULL;
	elem_f->t_we = NULL;
	elem_f->t_ea = NULL;
	elem_f->t_sprite = NULL;
	elem_f->ground = -1;
	elem_f->ceiling = -1;
	elem_f->start_x = -1;
	elem_f->start_y = -1;
	elem_f->map_width = 0;
	elem_f->map_size = 0;
	elem_f->map_index = -1;
	elem_f->bit_pxl = 32;
	elem_f->file_size = 0;
}

t_player	init_struct_player(t_window *ptr)
{
	t_player	player;

	player.pos_x = ptr->info_file.start_x + 0.5;
	player.pos_y = ptr->info_file.start_y + 0.5;
	player.f_x = 0;
	player.f_y = 0;
	return (player);
}

void	init_struct_ptr(t_window *ptr)
{
	t_info_file	info_file;

	init_struct_file(&info_file);
	ptr->win = NULL;
	ptr->mlx = NULL;
	ptr->img = NULL;
	ptr->is_press = 0;
	ptr->ratio = 10;
	ptr->info_file = info_file;
	ptr->save = 0;
	init_struct_ray(ptr);
	input_init(ptr);
}
