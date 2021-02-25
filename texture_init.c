/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:22:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/25 10:59:36 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	init_text_struct(t_window *ptr)
{
	t_texture texture;

	texture.ptr = mlx_xpm_file_to_image (ptr->mlx, ptr->info_file.t_no,
		&texture.width, &texture.height);
	texture.addr = (int *)mlx_get_data_addr (texture.ptr,
		&texture.bits_pxl, &texture.len_line, &texture.endian);
	return(texture);
}

void	check_text_errors(t_window *ptr)
{
	if (!ptr->texture_n.ptr)
		ft_error(5);
	if (!ptr->texture_s.ptr)
		ft_error(5);
	if (!ptr->texture_e.ptr)
		ft_error(5);
	if (!ptr->texture_o.ptr)
		ft_error(5);
}

void	create_text_strcut(t_window *ptr)
{
	ptr->texture_n = init_text_struct(ptr);
	ptr->texture_s = init_text_struct(ptr);
	ptr->texture_e = init_text_struct(ptr);
	ptr->texture_o = init_text_struct(ptr);
	init_text_struct(ptr);
	check_text_errors(ptr);
}