/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 14:40:36 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:10:47 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab, int len)
{
	while (--len >= 0)
		free(tab[len]);
	free(tab);
}

void	free_tex(t_window *ptr, t_texture *tex, char **path)
{
	if (tex->ptr)
		mlx_destroy_image(ptr->mlx, tex->ptr);
	free(*path);
}

void	ft_free_all_tex(t_window *ptr)
{
	if (ptr->info_file.t_no)
		free_tex(ptr, &ptr->n_tex, &ptr->info_file.t_no);
	if (ptr->info_file.t_so)
		free_tex(ptr, &ptr->s_tex, &ptr->info_file.t_so);
	if (ptr->info_file.t_ea)
		free_tex(ptr, &ptr->e_tex, &ptr->info_file.t_ea);
	if (ptr->info_file.t_we)
		free_tex(ptr, &ptr->o_tex, &ptr->info_file.t_we);
	if (ptr->info_file.t_sprite)
		free_tex(ptr, &ptr->sp_tex, &ptr->info_file.t_sprite);
	if (ptr->info_file.t_end_sprite)
		free_tex(ptr, &ptr->end_sp_tex, &ptr->info_file.t_end_sprite);
	if (ptr->info_file.t_trap_sprite)
		free_tex(ptr, &ptr->trap_sp_tex, &ptr->info_file.t_trap_sprite);
	if (ptr->info_file.t_heal_sprite)
		free_tex(ptr, &ptr->heal_sp_tex, &ptr->info_file.t_heal_sprite);
	if (ptr->info_file.skybox)
		free_tex(ptr, &ptr->skybox, &ptr->info_file.skybox);
}

void	free_file(t_window *ptr)
{
	if (ptr->info_file.cpy_map)
		free_tab(ptr->info_file.cpy_map, ptr->info_file.cpy_map_allo_size);
	if (ptr->info_file.file)
		free_tab(ptr->info_file.file, ptr->info_file.file_size);
	if (ptr->info_file.map)
		free_tab(ptr->info_file.map, ptr->info_file.map_allo_size);
}

void	ft_freedom(t_window *ptr)
{
	int	i;

	i = ptr->info_file.sprite_allo_size;
	if (ptr->sprite)
	{
		while (i--)
			free(ptr->sprite[i]);
		free(ptr->sprite);
	}
	if (ptr->image.ptr)
		mlx_destroy_image(ptr->mlx, ptr->image.ptr);
	if (ptr->fov.dist)
		free(ptr->fov.dist);
	if (ptr->fov.shade)
		free(ptr->fov.shade);
	free_file(ptr);
	ft_free_all_tex(ptr);
	if (ptr->mlx && ptr->win)
		mlx_destroy_window(ptr->mlx, ptr->win);
}
