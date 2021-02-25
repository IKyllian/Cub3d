/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:14:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/25 10:02:28 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_start_pos(t_window *ptr, int *start_pos, int i, int j)
{
	int index;

	index = ptr->info_file.map_index;
	if ((ptr->info_file.file[i + index][j] == 'N' || ptr->info_file.file[i + index][j] == 'S' ||
		ptr->info_file.file[i + index][j] == 'E' || ptr->info_file.file[i + index][j] == 'W') && *start_pos)
		ft_error(2);
	else if ((ptr->info_file.file[i + index][j] == 'N' || ptr->info_file.file[i + index][j] == 'S' ||
		ptr->info_file.file[i + index][j] == 'E' || ptr->info_file.file[i + index][j] == 'W') && !*start_pos)
	{
		ptr->info_file.start_x = j;
		ptr->info_file.start_y = i;
		*start_pos = 1;
	}
}

void	fill_map_tab(t_window *ptr, int i, int max_size, int *start_pos)
{
	int j;

	j = -1;
	if (!(ptr->info_file.cpy_map[i] = malloc(sizeof(char) * max_size)))
			ft_error(4);
		j = -1;
		while (ptr->info_file.file[i + ptr->info_file.map_index][++j])
		{
			check_start_pos(ptr, start_pos, i, j);
			if (ptr->info_file.file[i + ptr->info_file.map_index][j] == '1')
				ptr->info_file.cpy_map[i][j] = '1';
			else if (ptr->info_file.file[i + ptr->info_file.map_index][j] == ' ')
				ptr->info_file.cpy_map[i][j] = ' ';
			else if (ptr->info_file.file[i + ptr->info_file.map_index][j] != '1'
				&& ptr->info_file.file[i + ptr->info_file.map_index][j] != ' ')
				ptr->info_file.cpy_map[i][j] = '0';
		}
		while (j < max_size)
			ptr->info_file.cpy_map[i][j++] = ' ';
		if (ptr->info_file.map_width < ft_strlen(ptr->info_file.cpy_map[i]))
			ptr->info_file.map_width = ft_strlen(ptr->info_file.cpy_map[i]); //OPTI: Chaques lignes font la meme taille (pas besoin de la condition)
		ptr->info_file.cpy_map[i][j] = 0;
}

void	fill_map_cpy(t_window *ptr)
{
	int i;
	int start_pos;
	int max_size;

	i = -1;
	start_pos = 0;
	max_size = 0;
	while (ptr->info_file.file[++i])
		if (ft_strlen(ptr->info_file.file[i]) > max_size)
			max_size = ft_strlen(ptr->info_file.file[i]);
	i = -1;
	while (ptr->info_file.file[++i + ptr->info_file.map_index])
		fill_map_tab(ptr, i, max_size, &start_pos);
	ptr->info_file.cpy_map[i] = NULL;
	if (!start_pos)
		ft_error(3);
}