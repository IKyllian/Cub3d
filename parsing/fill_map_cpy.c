/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map_cpy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:14:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 13:26:11 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_start_pos(t_window *ptr, int *start_pos, int i, int j)
{
	if ((ptr->info_file.map[i][j] == 'N' || ptr->info_file.map[i][j] == 'S'
			|| ptr->info_file.map[i][j] == 'E'
			|| ptr->info_file.map[i][j] == 'W') && *start_pos)
		ft_error("Il ne peut y avoir que une position de depart", 1, ptr, 0);
	else if ((ptr->info_file.map[i][j] == 'N' || ptr->info_file.map[i][j] == 'S'
			|| ptr->info_file.map[i][j] == 'E'
			|| ptr->info_file.map[i][j] == 'W')
		&& !*start_pos)
	{
		ptr->info_file.start_x = j;
		ptr->info_file.start_y = i;
		*start_pos = 1;
	}
}

void	fill_character(t_window *ptr, int i, int j)
{
	if (ptr->info_file.map[i][j] == '2' || ptr->info_file.map[i][j] == '4'
		|| ptr->info_file.map[i][j] == '5'
		|| ptr->info_file.map[i][j] == '6')
		ptr->info_file.nb_sprite++;
	if (ptr->info_file.map[i][j] == '1')
		ptr->info_file.cpy_map[i][j] = '1';
	else if (ptr->info_file.map[i][j] == '3')
		ptr->info_file.cpy_map[i][j] = '3';
	else if (ptr->info_file.map[i][j] == ' ')
		ptr->info_file.cpy_map[i][j] = ' ';
	else if (ptr->info_file.map[i][j] != '1'
		&& ptr->info_file.map[i][j] != ' ')
		ptr->info_file.cpy_map[i][j] = '0';
}

void	fill_map_tab(t_window *ptr, int i, int max_size, int *start_pos)
{
	int	j;

	ptr->info_file.cpy_map[i] = malloc(sizeof(char) * (max_size + 1));
	if (!ptr->info_file.cpy_map[i])
		ft_error("Erreur d'allocation.", 1, ptr, 0);
	ptr->info_file.cpy_map_allo_size++;
	j = -1;
	while (ptr->info_file.map[i][++j])
	{
		check_start_pos(ptr, start_pos, i, j);
		fill_character(ptr, i, j);
	}
	while (j < max_size)
		ptr->info_file.cpy_map[i][j++] = ' ';
	ptr->info_file.cpy_map[i][j] = 0;
}

void	fill_map_cpy(t_window *ptr)
{
	int	i;
	int	start_pos;
	int	max_size;

	i = -1;
	start_pos = 0;
	max_size = 0;
	while (ptr->info_file.map[++i])
		if (ft_strlen(ptr->info_file.map[i]) > max_size)
			max_size = ft_strlen(ptr->info_file.map[i]);
	ptr->info_file.map_width = max_size;
	i = -1;
	while (ptr->info_file.map[++i])
		fill_map_tab(ptr, i, max_size, &start_pos);
	ptr->info_file.cpy_map[i] = NULL;
	if (!start_pos)
		ft_error("Il doit y avoir au moins une position de depart.", 1, ptr, 0);
}
