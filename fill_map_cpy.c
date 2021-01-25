/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:14:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/25 10:14:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_start_pos(t_info_file *elem_f, int *start_pos, int i, int j)
{
	int index;

	index = elem_f->map_index;
	if ((elem_f->file[i + index][j] == 'N' || elem_f->file[i + index][j] == 'S' ||
		elem_f->file[i + index][j] == 'E' || elem_f->file[i + index][j] == 'W') && *start_pos)
		error_wall_map(2);
	else if ((elem_f->file[i + index][j] == 'N' || elem_f->file[i + index][j] == 'S' ||
		elem_f->file[i + index][j] == 'E' || elem_f->file[i + index][j] == 'W') && !*start_pos)
	{
		elem_f->start_x = i;
		elem_f->start_y = j;
		*start_pos = 1;
	}
}

void	fill_map_tab(t_info_file *elem_f, int i, int max_size, int *start_pos)
{
	int j;

	j = -1;
	if (!(elem_f->cpy_map[i] = malloc(sizeof(char) * max_size)))
			error_wall_map(4);
		j = -1;
		while (elem_f->file[i + elem_f->map_index][++j])
		{
			check_start_pos(elem_f, start_pos, i, j);
			if (elem_f->file[i + elem_f->map_index][j] == '1')
				elem_f->cpy_map[i][j] = '1';
			else if (elem_f->file[i + elem_f->map_index][j] != '1')
				elem_f->cpy_map[i][j] = '0';
		}
		while (j < max_size)
			elem_f->cpy_map[i][j++] = ' ';
		elem_f->cpy_map[i][j] = 0;
}

void	fill_map_cpy(t_info_file *elem_f)
{
	int i;
	int j;
	int start_pos;
	int max_size;

	i = -1;
	start_pos = 0;
	max_size = 0;
	while (elem_f->file[++i])
		if (ft_strlen(elem_f->file[i]) > max_size)
			max_size = ft_strlen(elem_f->file[i]);
	i = -1;
	while (elem_f->file[++i + elem_f->map_index])
		fill_map_tab(elem_f, i, max_size, &start_pos);
	elem_f->cpy_map[i] = NULL;
	if (!start_pos)
		error_wall_map(3);
}