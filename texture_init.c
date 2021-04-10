/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:22:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 14:50:41 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_text_struct(t_window *ptr, t_texture *texture, char *tex)
{
	texture->ptr = mlx_xpm_file_to_image(ptr->mlx, tex,
			&texture->width, &texture->height);
	if (!texture->ptr)
		ft_error("Un fichier de texture n'existe pas", 1, ptr, 0);
	texture->addr = (int *)mlx_get_data_addr(texture->ptr,
			&texture->bits_pxl, &texture->len_line, &texture->endian);
}

t_texture	init_text_struct(void)
{
	t_texture	texture;

	texture.addr = NULL;
	texture.ptr = NULL;
	texture.bits_pxl = 0;
	texture.endian = 0;
	texture.height = 0;
	texture.len_line = 0;
	texture.width = 0;
	return (texture);
}

void	create_text_struct(t_window *ptr)
{
	fill_text_struct(ptr, &ptr->n_tex, ptr->info_file.t_no);
	fill_text_struct(ptr, &ptr->s_tex, ptr->info_file.t_so);
	fill_text_struct(ptr, &ptr->e_tex, ptr->info_file.t_ea);
	fill_text_struct(ptr, &ptr->o_tex, ptr->info_file.t_we);
}
