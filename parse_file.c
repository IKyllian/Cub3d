/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/25 16:14:20 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	//Penser a gerer les espaces au milieu du fichier
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

// void	display_map(t_info_file *elem_f, t_window *ptr)
// {
// 	int i;
// 	int j;
// 	int compt;

// 	i = 0;
// 	while (elem_f->file[i])
// 	{
// 		compt = 0;
// 		j = -1;
// 		while (elem_f->file[i][++j])
// 		{
// 			if (elem_f->file[i][j] != ' ')
// 			{
// 				if (elem_f->file[i][++j] == '1')
// 				{
// 					compt++;
// 					mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 248, 123, 9));
// 				}
// 			}
// 		}
// 	}

// }

int main()
{
	t_info_file elem_f;
	t_window	ptr;

	init_struct_file(&elem_f);
	init_struct_ptr(&ptr);
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

	ptr.mlx = mlx_init();
 	ptr.win = mlx_new_window(ptr.mlx, elem_f.res_x, elem_f.res_y, "Window test");
	mlx_key_hook(ptr.win, key_pressed, &ptr);
	mlx_loop(ptr.mlx);
	//free_tab(elem_f.file);
	return (0);
}