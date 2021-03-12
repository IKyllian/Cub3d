/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:22:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/12 14:29:36 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	init_text_struct(t_window *ptr, char *tex)
{
	t_texture texture;

	texture.ptr = mlx_xpm_file_to_image(ptr->mlx, tex,
		&texture.width, &texture.height);
	texture.addr = (int *)mlx_get_data_addr(texture.ptr,
		&texture.bits_pxl, &texture.len_line, &texture.endian);
	return(texture);
}

void	check_text_errors(t_window *ptr)
{
	if (!ptr->n_tex.ptr)
		ft_error(5);
	else if (!ptr->s_tex.ptr)
		ft_error(5);
	else if (!ptr->e_tex.ptr)
		ft_error(5);
	else if (!ptr->o_tex.ptr)
		ft_error(5);
}

void	create_text_struct(t_window *ptr)
{
	ptr->n_tex = init_text_struct(ptr, ptr->info_file.t_no);
	ptr->s_tex = init_text_struct(ptr, ptr->info_file.t_so);
	ptr->e_tex = init_text_struct(ptr, ptr->info_file.t_ea);
	ptr->o_tex = init_text_struct(ptr, ptr->info_file.t_we);
	check_text_errors(ptr);
}