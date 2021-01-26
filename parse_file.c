/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/26 14:38:37 by kdelport         ###   ########lyon.fr   */
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

void	print_map(char c, t_window *ptr, int x, int y)
{
	if (c == '1')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 255, 153, 51));
	else if (c == '2')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 0, 0, 255));
	else if (c == 'N' || c == 'S' || c == 'E' ||c == 'W')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 0, 153, 73));
	else if (c == '0')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 255, 255, 255));
}

void	display_map(t_info_file *elem_f, t_window *ptr)
{
	int y;
	int x;
	char **map;
	int compt;

	y = 0;
	compt = 0;
	map = elem_f->file + elem_f->map_index;
	while (y / 30 < elem_f->map_size)
	{
		x = 0;
		while (x / 30 < ft_strlen(map[y / 30]) && map[y / 30][x / 30])
		{
			compt++;
			print_map(map[y / 30][x / 30], ptr, x, y);	
			x++;
		}
		y++;
	}
	printf("compt = %i\n", compt);
}

void	display_player(t_info_file *elem_f, t_window *ptr)
{
	mlx_pixel_put(ptr->mlx, ptr->win, elem_f->start_y * 30, elem_f->start_x * 30, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, elem_f->start_y * 30 + 1, elem_f->start_x * 30 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, elem_f->start_y * 30 - 1 , elem_f->start_x * 30 - 1, create_trgb(0, 255, 0, 0));
	//mlx_pixel_put(ptr->mlx, ptr->win, elem_f->start_x * 0, elem_f->start_y * 10, create_trgb(0, 255, 0, 0));
}

int main()
{
	t_info_file elem_f;
	t_window	ptr;
	t_player	player;

	init_struct_file(&elem_f);
	init_struct_ptr(&ptr);
	init_struct_player(&player);
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
	display_map(&elem_f, &ptr);
	display_player(&elem_f, &ptr);
	mlx_key_hook(ptr.win, key_pressed, &ptr);
	mlx_loop(ptr.mlx);
	free_tab(elem_f.file);
	return (0);
}