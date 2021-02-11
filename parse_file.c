/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by kdelport          #+#    #+#             */
/*   Updated: 2021/02/08 11:38:38 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int y, int x, t_window *ptr)
{
	char ***map;

	map = &ptr->info_file.cpy_map;
	if ((*map)[y][x] == '1' || (*map)[y][x] == 'o')
		return ;	
	(*map)[y][x] = 'o';
	if (y - 1 >= 0 && x < ft_strlen((*map)[y - 1]))
		flood_fill(y - 1, x, ptr); // North
	if (y - 1 >= 0 && x + 1 < ft_strlen((*map)[y - 1]))
	  	flood_fill(y - 1, x + 1, ptr); //Diagonal North East
	if (y - 1 >= 0 && x - 1 >= 0)
	   	flood_fill(y - 1, x - 1, ptr); //Diagonal North West
	if (y + 1 < ptr->info_file.map_size && x < ft_strlen((*map)[y + 1]))
		flood_fill(y + 1, x, ptr); //South
	if (y + 1 < ptr->info_file.map_size && x + 1 < ft_strlen((*map)[y + 1]))
	  	flood_fill(y + 1, x + 1, ptr); //Diagonal South East
	if (y + 1 < ptr->info_file.map_size && x - 1 >= 0)
	  	flood_fill(y + 1, x - 1, ptr); //Diagonal South West
	if (x + 1 < ft_strlen((*map)[y]))
		flood_fill(y, x + 1, ptr); //East
	if (x - 1 >= 0)
		flood_fill(y, x - 1, ptr); //West
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

int main()
{
	t_window	ptr;

	init_struct_ptr(&ptr);
	if (!(ptr.info_file.file = malloc(sizeof(char *) * (get_file_size() + 1))))
	 	return (0);
	fill_tab(&ptr);
	if (!(ptr.info_file.cpy_map = malloc(sizeof(char *) * (ptr.info_file.map_size + 1))))
		return (0);
	fill_map_cpy(&ptr);
	// print_str_debug(ptr.info_file.file);
	// print_str_debug(ptr.info_file.cpy_map);
	flood_fill(ptr.info_file.start_y, ptr.info_file.start_x, &ptr);
	// print_str_debug(ptr.info_file.cpy_map);
	if (!map_is_valid(ptr.info_file.cpy_map, ptr.info_file.map_size))
	 	error_wall_map(1);
	if (parse_file(&ptr) == -1)
		error_wall_map();
	ptr.player.pos_x = ptr.info_file.start_x + 0.5;
	ptr.player.pos_y = ptr.info_file.start_y + 0.5;
	ptr.player.vect_y = -2;
	ptr.player.vect_x = 0;
	printf("map width = %i\n", ptr.info_file.map_width);
	create_window(&ptr);
	free_tab(ptr.info_file.file);
	return (0);
}