/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/26 16:25:41 by kdelport         ###   ########lyon.fr   */
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

void	display_map(t_window *ptr)
{
	int y;
	int x;
	char **map;
	int compt;

	y = 0;
	compt = 0;
	map = ptr->info_file.file + ptr->info_file.map_index;
	while (y / 60 < ptr->info_file.map_size)
	{
		x = 0;
		while (x / 60 < ft_strlen(map[y / 60]) && map[y / 60][x / 60])
		{
			compt++;
			print_map(map[y / 60][x / 60], ptr, x, y);	
			x++;
		}
		y++;
	}
	printf("compt = %i\n", compt);
}



void	display_player(t_window *ptr)
{
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 0, 0));
}

void	remove_player(t_window *ptr)
{
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 + 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 + 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 60 - 1, ptr->player.pos_y * 60 - 1, create_trgb(0, 255, 255, 255));
}

int		key_move(int keycode, t_window *ptr)
{
	remove_player(ptr);
	//printf("keycode = %i\n", keycode);
	if (keycode == 13 || keycode == 126) // Touche w et fleche haut
		ptr->player.pos_y -= 0.5;
	else if (keycode == 0 || keycode == 123) // A
		ptr->player.pos_x -= 0.5;
	else if (keycode == 2 || keycode == 124) // D
		ptr->player.pos_x += 0.5;
	if (keycode == 1 || keycode == 125) // Touche s et fleche bas
		ptr->player.pos_y += 0.5;
	display_player(ptr);
	return (0);
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
	print_str_debug(ptr.info_file.file);
	print_str_debug(ptr.info_file.cpy_map);
	flood_fill(ptr.info_file.start_y, ptr.info_file.start_x, &ptr);
	print_str_debug(ptr.info_file.cpy_map);
	if (!map_is_valid(ptr.info_file.cpy_map, ptr.info_file.map_size))
	 	error_wall_map(1);
	if (parse_file(&ptr) == -1)
		error_wall_map();
	ptr.player.pos_x = ptr.info_file.start_x + 0.5;
	ptr.player.pos_y = ptr.info_file.start_y + 0.5;
	ptr.mlx = mlx_init();
 	ptr.win = mlx_new_window(ptr.mlx, ptr.info_file.res_x, ptr.info_file.res_y, "Window test");
	display_map(&ptr);
	display_player(&ptr);
	mlx_key_hook(ptr.win, key_quit, &ptr);
	mlx_hook(ptr.win, 2, 1L<<0, key_move, &ptr);
	mlx_loop(ptr.mlx);
	free_tab(ptr.info_file.file);
	return (0);
}