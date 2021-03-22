/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:58:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/22 14:01:50 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_is_valid(t_window *ptr)
{
	if (!ptr->info_file.t_no || !ptr->info_file.t_so || !ptr->info_file.t_we
		|| !ptr->info_file.t_ea || (ptr->info_file.res_x < 0 && \
		ptr->info_file.res_y < 0) || !ptr->info_file.t_sprite
		|| ptr->info_file.ground < 0 || ptr->info_file.ceiling < 0)
		return (0);
	else
		return (1);
}

void	line_is_false(char *line, int ret, t_window *ptr)
{
	if (ptr->info_file.map_index > 0 && ret > 0 && line[0] == '\0')
		ft_error(8, ptr);
	if (line[0] != 'R' && line[0] != 'N' && line[0] != 'S' && line[0] != 'E'
		&& line[0] != 'W' && line[0] != 'S' && line[0] != 'F'
		&& line[0] != 'C' && line[0] != ' ' && line[0] != '\t'
		&& line[0] != '1' && line[0] != '2' && line[0] != '0'
		&& line[0] != '\0')
		ft_error(9, ptr);
}

void	get_number(char **str, t_window *ptr, int *color, int is_color)
{
	while (*(*str) && (*(*str) == ' ' || *(*str) == '\t'
			|| (is_color && *(*str) == ',')))
		(*str)++;
	if (*(*str) < 48 || *(*str) > 57)
		ft_error(8, ptr);
	while (*(*str) && (*(*str) >= 48 && *(*str) <= 57))
		*color = *color * 10 + (*(*str)++ - 48);
}
