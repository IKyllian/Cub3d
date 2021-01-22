/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 15:28:57 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_map_cpy(t_info_file *elem_f)
{
	int i;
	int j;
	int start_pos;
	int max_size;

	i = -1;
	start_pos = 0;

	printf("size = %i | index = %i", elem_f->map_size, elem_f->map_index);
	i = -1;
	while (++i < elem_f->map_size)
		elem_f->cpy_map[i] = ft_strdup(elem_f->map[elem_f->map_index + i]);
	elem_f->cpy_map[i] = NULL;
	i = -1;
	while (elem_f->cpy_map[++i])
	{
		j = -1;
		while (elem_f->cpy_map[i][++j])
		{
			if ((elem_f->cpy_map[i][j] == 'N' || elem_f->cpy_map[i][j] == 'S' ||
				elem_f->cpy_map[i][j] == 'E' || elem_f->cpy_map[i][j] == 'W') && start_pos)
				error_wall_map(2);
			else if ((elem_f->cpy_map[i][j] == 'N' || elem_f->cpy_map[i][j] == 'S' ||
				elem_f->cpy_map[i][j] == 'E' || elem_f->cpy_map[i][j] == 'W') && !start_pos)
			{
				elem_f->start_x = i;
				elem_f->start_y = j;
				start_pos = 1;
			}
			if (elem_f->cpy_map[i][j] != '1')
				elem_f->cpy_map[i][j] = '0';
		}
	}
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
	if (x - 1 >= 0 && y < ft_strlen((*map)[x - 1]))
		flood_fill(x - 1, y, elem_f); // North
	if (x - 1 >= 0 && y + 1 < ft_strlen((*map)[x - 1]))
	  	flood_fill(x - 1, y + 1, elem_f); //Diagonal North East
	if (x - 1 >= 0 && y - 1 >= 0)
	   	flood_fill(x - 1, y - 1, elem_f); //Diagonal North West
	if (x + 1 < elem_f->map_size && y < ft_strlen((*map)[x + 1]))
		flood_fill(x + 1, y, elem_f); //South
	if (x + 1 < elem_f->map_size && y + 1 < ft_strlen((*map)[x + 1]))
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
	if (!(elem_f.map = malloc(sizeof(char *) * (get_file_size() + 1))))
	 	return (0);
	fill_tab(&elem_f);
	if (!(elem_f.cpy_map = malloc(sizeof(char *) * (elem_f.map_size + 1))))
		return (0);
	fill_map_cpy(&elem_f);
	print_str_debug(elem_f.map);
	print_str_debug(elem_f.cpy_map);
	flood_fill(elem_f.start_x, elem_f.start_y, &elem_f);
	print_str_debug(elem_f.cpy_map);
	if (!map_is_valid(elem_f.cpy_map, elem_f.map_size))
	 	error_wall_map(1);
	if (parse_file(&elem_f) == -1)
		error_wall_map();
	//free_tab(elem_f.map);
	return (0);
}