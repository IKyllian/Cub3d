/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 20:53:20 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/27 16:26:40 by kdelport         ###   ########lyon.fr   */
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
	while (y / 20 < ptr->info_file.map_size)
	{
		x = 0;
		while (x / 20 < ft_strlen(map[y / 20]) && map[y / 20][x / 20])
		{
			compt++;
			print_map(map[y / 20][x / 20], ptr, x, y);	
			x++;
		}
		y++;
	}
	printf("compt = %i\n", compt);
}



void	display_player(t_window *ptr)
{
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20, create_trgb(0, 255, 255, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 + 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20 - 1, create_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 - 1, create_trgb(0, 255, 0, 0));
}

void	remove_player(t_window *ptr)
{
	//printf("Pos x = %i | Pos y = %i\n", (int)ptr->player.pos_x, (int)ptr->player.pos_y);
	int color;
	char **map = ptr->info_file.file + ptr->info_file.map_index;
	char c;

	c = map[(int)ptr->player.pos_y][(int)ptr->player.pos_x];
	color = 0;
	//printf("c = %c\n", c);
	if (c == '1')
		color = create_trgb(0, 255, 153, 51);
	else if (c == '2')
		color = create_trgb(0, 0, 0, 255);
	else if (c == 'N' || c == 'S' || c == 'E' ||c == 'W')
		color = create_trgb(0, 0, 153, 73);
	else if (c == '0')
		color = create_trgb(0, 255, 255, 255);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20 - 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20, ptr->player.pos_y * 20 + 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20 + 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 - 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 + 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 + 1, ptr->player.pos_y * 20 - 1, color);
	mlx_pixel_put(ptr->mlx, ptr->win, ptr->player.pos_x * 20 - 1, ptr->player.pos_y * 20 - 1, color);
}

int is_collision(float pos, t_window *ptr, int dir)
{
	char **map;
	int pos_cast;

	pos_cast = (int)pos;
	map = ptr->info_file.file + ptr->info_file.map_index;
	printf("pos = %f\n", pos);
	if (dir == 1 && pos >= 0 &&
		map[pos_cast][(int)ptr->player.pos_x] != '1' &&
		map[pos_cast][(int)ptr->player.pos_x] != '2')
		return (0);
	else if (dir == 2 && pos_cast < ptr->info_file.map_size &&
			map[pos_cast][(int)ptr->player.pos_x] != '1' &&
			map[pos_cast][(int)ptr->player.pos_x] != '2')
		return (0);
	else if (dir == 3 && pos_cast < ft_strlen(map[(int)ptr->player.pos_y]) &&
			map[(int)ptr->player.pos_y][pos_cast] != '1' &&
			map[(int)ptr->player.pos_y][pos_cast] != '2')
		return (0);
	else if (dir == 4 && pos >= 0 &&
			map[(int)ptr->player.pos_y][pos_cast] != '1' &&
			map[(int)ptr->player.pos_y][pos_cast] != '2')
		return (0);
	return (1);
}

int		key_move(int keycode, t_window *ptr)
{
	remove_player(ptr);
	//printf("keycode = %i\n", keycode);
	if ((keycode == 13 || keycode == 126) && !is_collision(ptr->player.pos_y - 0.1, ptr, 1)) // Touche w et fleche haut
		ptr->player.pos_y -= 0.1;
	else if ((keycode == 1 || keycode == 125) && !is_collision(ptr->player.pos_y + 0.1, ptr, 2)) // Touche s et fleche bas
		ptr->player.pos_y += 0.1;
	else if ((keycode == 2 || keycode == 124) && !is_collision(ptr->player.pos_x + 0.1, ptr, 3)) // d et fleche droite
		ptr->player.pos_x += 0.1;
	else if ((keycode == 0 || keycode == 123) && !is_collision(ptr->player.pos_x - 0.1, ptr, 4)) // a et fleche gauche
		ptr->player.pos_x -= 0.1;
	
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