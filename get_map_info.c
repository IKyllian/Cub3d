/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/18 16:19:19 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_info_texture(char letter, int *index, t_elem_file *info_file)
{
	*index += 2;

	if (letter == 'N')
		info_file->t_no = 1;
	else if (letter == 'S')
		info_file->t_so = 1;
	else if (letter == 'E')
		info_file->t_ea = 1;
	else if (letter == 'W')
		info_file->t_we = 1;
	
}

void	get_color_res(char letter, int *index, t_elem_file *info_file)
{
	(*index)++;
	if (letter == 'R')
		;
	else if (letter == 'S')
		;
	else if (letter == 'F')
		;
	else if (letter == 'C')
		;
	
}