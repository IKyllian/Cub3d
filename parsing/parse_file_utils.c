/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 11:48:58 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:14:04 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	fill_file_map(t_window *ptr, char *line, int *i, int *j)
{
	if (!line_is_map(line))
	{
		ptr->info_file.file[(*i)++] = line;
		ptr->info_file.file_size++;
	}
	else
	{
		ptr->info_file.map[(*j)++] = line;
		ptr->info_file.map_allo_size++;
	}
}

void	check_map_error(t_window *ptr, char *line, int index)
{
	get_map_size(line, ptr, index);
	if (ptr->info_file.map_index > 0 && !line_is_map(line))
	{
		if (line)
			free(line);
		ft_error("Le dernier element du fichier doit etre la map", \
			1, ptr, 1);
	}
}
