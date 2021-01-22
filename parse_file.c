/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 16:29:53 by kdelport         ###   ########lyon.fr   */
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
	//while (++i < elem_f->map_size)
	//	elem_f->cpy_map[i] = ft_strdup(elem_f->map[elem_f->map_index + i]);
	printf("max_size = %i\n", max_size);
	while (elem_f->file[++i + elem_f->map_index])
	{
		if (!(elem_f->cpy_map[i] = malloc(sizeof(char) * max_size)))
			error_wall_map(4);
		//elem_f->cpy_map[i] = ft_calloc(sizeof(char), max_size);
		j = -1;
		while (elem_f->file[i + elem_f->map_index][++j])
		{
			check_start_pos(elem_f, &start_pos, i, j);
			if (elem_f->file[i + elem_f->map_index][j] == '1')// && (j < ft_strlen(elem_f->file[i]) - 1))
				elem_f->cpy_map[i][j] = '1';
			else if (elem_f->file[i + elem_f->map_index][j] != '1')// && (j < ft_strlen(elem_f->file[i]) - 1))
				elem_f->cpy_map[i][j] = '0';
		}
		while (j < max_size)
			elem_f->cpy_map[i][j++] = ' ';
		elem_f->cpy_map[i][j] = 0;
	}
	elem_f->cpy_map[i] = NULL;
	if (!start_pos)
		error_wall_map(3);
}

void	flood_fill(int x, int y, t_info_file *elem_f)
{
	char ***map;

	map = &elem_f->cpy_map;
	if ((*map)[x][y] == '1' || (*map)[x][y] == 'o')
		return ;	
	(*map)[x][y] = 'o';
	if (x - 1 >= 0 && (*map)[x - 1][y] != ' ')
		flood_fill(x - 1, y, elem_f); // North
	if (x - 1 >= 0 && (*map)[x - 1][y + 1] != ' ')
	  	flood_fill(x - 1, y + 1, elem_f); //Diagonal North East
	if (x - 1 >= 0 && y - 1 >= 0)
	   	flood_fill(x - 1, y - 1, elem_f); //Diagonal North West
	if (x + 1 < elem_f->map_size && (*map)[x - 1][y] != ' ')
		flood_fill(x + 1, y, elem_f); //South
	if (x + 1 < elem_f->map_size && (*map)[x - 1][y + 1] != ' ')
	  	flood_fill(x + 1, y + 1, elem_f); //Diagonal South East
	if (x + 1 < elem_f->map_size && y - 1 >= 0)
	  	flood_fill(x + 1, y - 1, elem_f); //Diagonal South West
	if (y + 1 < ft_strlen((*map)[x]))
		flood_fill(x, y + 1, elem_f); //East
	if (y - 1 >= 0)
		flood_fill(x, y - 1, elem_f); //West
	return ;
}

void	free_tab(char **tab)
{
	while (*tab)
		free(*tab++);
	free(tab);
}

void	print_str_debug(char **str)
{
	int i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
	printf("\n");
}

int main()
{
	t_info_file elem_f;

	init_struct_file(&elem_f);
	if (!(elem_f.file = malloc(sizeof(char *) * (get_file_size() + 1))))
	 	return (0);
	fill_tab(&elem_f);
	if (!(elem_f.cpy_map = malloc(sizeof(char *) * (elem_f.map_size + 1))))
		return (0);
	fill_map_cpy(&elem_f);
	print_str_debug(elem_f.file);
	print_str_debug(elem_f.cpy_map);
	flood_fill(elem_f.start_x, elem_f.start_y, &elem_f);
	print_str_debug(elem_f.cpy_map);
	if (!map_is_valid(elem_f.cpy_map, elem_f.map_size))
	 	error_wall_map(1);
	if (parse_file(&elem_f) == -1)
		error_wall_map();
	//free_tab(elem_f.file);
	return (0);
}