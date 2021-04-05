/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 12:58:50 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/05 15:53:21 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	file_is_valid(t_window *ptr)
{
	if (!ptr->info_file.t_no || !ptr->info_file.t_so || !ptr->info_file.t_we
		|| !ptr->info_file.t_ea || (ptr->info_file.res_x < 0 && \
		ptr->info_file.res_y < 0) || !ptr->info_file.t_sprite
		|| ptr->info_file.ground < 0 || ptr->info_file.ceiling < 0)
	{
		if (ptr->info_file.res_x == 0 || ptr->info_file.res_y == 0)
			ft_error("La resolution doit etre superieur a 0", 1, ptr);
		return (0);
	}
	else if ((ptr->info_file.has_second_sprite && !ptr->info_file.t_second_sprite)
			|| (ptr->info_file.has_trap_sprite && !ptr->info_file.t_trap_sprite)
			|| (ptr->info_file.has_heal_sprite && !ptr->info_file.t_heal_sprite))
	{
		ft_error("Un fichier de texture est manquant", 1, ptr);
		return (0);
	}
	else if ((!ptr->info_file.has_second_sprite && ptr->info_file.t_second_sprite)
			|| (!ptr->info_file.has_trap_sprite && ptr->info_file.t_trap_sprite)
			|| (!ptr->info_file.has_heal_sprite && ptr->info_file.t_heal_sprite))
	{
		ft_error("Un caractere est manquant dans la map ou un fichier de texture est en trop", 1, ptr);
		return (0);
	}
	else
		return (1);
}

int	map_character_is_valid(char *line, t_window *ptr)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != '0' && line[i] != ' ' && line[i] != '1'
			&& line[i] != '2' && line[i] != '3' && line[i] != '4'
			&& line[i] != '5' && line[i] != '6' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			ft_error("Un caractere est incorrecte dans la map", 1, ptr);
		else if (line[i] == '4')
			ptr->info_file.has_second_sprite = 1;
		else if (line[i] == '5')
			ptr->info_file.has_trap_sprite = 1;
		else if (line[i] == '6')
			ptr->info_file.has_heal_sprite = 1;
	}
	return (1);
}

void	get_number(char **str, t_window *ptr, int *color, int is_color)
{
	int comma_exist;

	comma_exist = 0;
	while (*(*str) && (*(*str) == ' ' || *(*str) == '\t'
			|| (is_color && *(*str) == ',')))
	{
		if (*(*str) == ',' && comma_exist)
			ft_error("Chaques couleurs doivent etre séparer par une virgule", 1, ptr);
		if (*(*str)++ == ',' && is_color)
			comma_exist = 1;
	}
	if (is_color && !comma_exist)
		ft_error("Chaques couleurs doivent etre séparer par une virgule", 1, ptr);
	if (*(*str) < 48 || *(*str) > 57)
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr);
	while (*(*str) && (*(*str) >= 48 && *(*str) <= 57))
		*color = *color * 10 + (*(*str)++ - 48);
}

void	get_map_size(char *line, t_window *ptr, int i)
{
	if (line_is_map(line) && map_character_is_valid(line, ptr))
	{
		if (ptr->info_file.map_index < 0)
			ptr->info_file.map_index = i;
		ptr->info_file.map_size += 1;
	}
}