/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by kdelport          #+#    #+#             */
/*   Updated: 2021/02/01 16:28:03 by kdelport         ###   ########lyon.fr   */
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

int		ft_color(char c)
{
	//printf(" C = %c\n", c);
	if (c == '1')
		return (ft_trgb(0, 255, 153, 51));
	else if (c == '2')
		return (ft_trgb(0, 0, 0, 255));
	else if (c == 'N' || c == 'S' || c == 'E' ||c == 'W')
		return (ft_trgb(0, 0, 153, 73));
	else if (c == '0')
		return (ft_trgb(0, 255, 255, 255));
	return (0);
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
	while (y / ptr->ratio < ptr->info_file.map_size)
	{
		x = 0;
		while (x / ptr->ratio < ft_strlen(map[y / ptr->ratio]) && map[y / ptr->ratio][x / ptr->ratio])
		{
			compt++;
			mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_color(map[y / ptr->ratio][x / ptr->ratio]));
			x++;
		}
		y++;
	}
	printf("compt = %i\n", compt);
}



void	display_player(t_window *ptr)
{
	int 	x;
	int 	y;
	int 	ratio;
	float 	vect_x;
	float 	vect_y;
	
	vect_x = ptr->player.pos_x +  ptr->player.vect_x;
	vect_y = ptr->player.pos_y + ptr->player.vect_y;
	ratio = ptr->ratio;
	x = ptr->player.pos_x * ratio;
	y = ptr->player.pos_y * ratio;
	mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, x - 1, y, ft_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, x, y - 1, ft_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, x + 1, y, ft_trgb(0, 255, 0, 0));
	mlx_pixel_put(ptr->mlx, ptr->win, x, y + 1, ft_trgb(0, 255, 0, 0));

	mlx_pixel_put(ptr->mlx, ptr->win, vect_x * ratio, vect_y * ratio, ft_trgb(0,255, 0, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, vect_x * ratio - 1, vect_y * ratio, ft_trgb(0,255, 0, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, vect_x * ratio, vect_y * ratio - 1, ft_trgb(0,255, 0, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, vect_x * ratio + 1, vect_y * ratio, ft_trgb(0,255, 0, 255));
	mlx_pixel_put(ptr->mlx, ptr->win, vect_x * ratio, vect_y * ratio + 1, ft_trgb(0,255, 0, 255));
}

void	remove_player(t_window *ptr)
{
	char **map = ptr->info_file.file + ptr->info_file.map_index;
	int x;
	int y;
	int ratio;

	ratio = ptr->ratio;
	x = ptr->player.pos_x * ratio;
	y = ptr->player.pos_y * ratio;
	mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_color(map[y / ratio][x / ratio]));
	mlx_pixel_put(ptr->mlx, ptr->win, x - 1, y, ft_color(map[y / ratio][(int)((x - 1) / ratio)]));
	mlx_pixel_put(ptr->mlx, ptr->win, x, y - 1, ft_color(map[(int)((y - 1) / ratio)][x / ratio]));
	mlx_pixel_put(ptr->mlx, ptr->win, x + 1, y, ft_color(map[y / ratio][(int)((x + 1) / ratio)]));
	mlx_pixel_put(ptr->mlx, ptr->win, x, y + 1, ft_color(map[(int)((y + 1) / ratio)][x / ratio]));

	// mlx_pixel_put(ptr->mlx, ptr->win, (ptr->player.pos_x +  ptr->player.vect_x) * ratio, (ptr->player.pos_y + ptr->player.vect_y) * ratio, ft_trgb(0,255, 0, 255));
	// mlx_pixel_put(ptr->mlx, ptr->win, (ptr->player.pos_x +  ptr->player.vect_x) * ratio - 1, (ptr->player.pos_y + ptr->player.vect_y) * ratio, ft_trgb(0,255, 0, 255));
	// mlx_pixel_put(ptr->mlx, ptr->win, (ptr->player.pos_x +  ptr->player.vect_x) * ratio, (ptr->player.pos_y + ptr->player.vect_y) * ratio - 1, ft_trgb(0,255, 0, 255));
	// mlx_pixel_put(ptr->mlx, ptr->win, (ptr->player.pos_x +  ptr->player.vect_x) * ratio + 1, (ptr->player.pos_y + ptr->player.vect_y) * ratio, ft_trgb(0,255, 0, 255));
	// mlx_pixel_put(ptr->mlx, ptr->win, (ptr->player.pos_x +  ptr->player.vect_x) * ratio, (ptr->player.pos_y + ptr->player.vect_y) * ratio + 1, ft_trgb(0,255, 0, 255));
}

int is_collision(float pos_x, float pos_y, t_window *ptr, int dir)
{
	char **map;
	int pos_y_cast;
	int pos_x_cast;

	(void)dir;
	pos_y_cast = (int)pos_y;
	pos_x_cast = (int)pos_x;
	map = ptr->info_file.file + ptr->info_file.map_index;
	if ((pos_y >= 0 || pos_y_cast < ptr->info_file.map_size || pos_y_cast < ft_strlen(map[(int)ptr->player.pos_y])) &&
		map[pos_y_cast][pos_x_cast] != '1' &&
		map[pos_y_cast][pos_x_cast] != '2') //Check Collision
		return (0);
	return (1);
}

int		key_move(int keycode, t_window *ptr)
{
	float x;
	float y;
	float vect_x;
	float vect_y;

	x = ptr->player.pos_x;
	y = ptr->player.pos_y;
	vect_x = ptr->player.vect_x;
	vect_y = ptr->player.vect_y;
	remove_player(ptr);
	//printf("keycode = %i\n", keycode);
	if ((keycode == 13 || keycode == 126) && !is_collision(x + vect_x * 0.1, y + vect_y * 0.1, ptr, 1)) // Touche w et fleche haut
	{
		ptr->player.pos_x = x + vect_x * 0.1;
		ptr->player.pos_y = y + vect_y * 0.1;
	}
	else if ((keycode == 1 || keycode == 125) && !is_collision(x - vect_x * 0.1, y - vect_y * 0.1, ptr, 2)) // Touche s et fleche bas
	{
		ptr->player.pos_x = x - vect_x * 0.1;
		ptr->player.pos_y = y - vect_y * 0.1;
	}
	else if ((keycode == 2 || keycode == 124)) //d et fleche droite
	{
		ptr->player.vect_x = vect_x * cos(0.1) - vect_y * sin(0.1);
		ptr->player.vect_y = vect_x * sin(0.1) + vect_y * cos(0.1);
	}
	else if ((keycode == 0 || keycode == 123)) // a et fleche gauche
	{
		ptr->player.vect_x = vect_x * cos(-0.1) - vect_y * sin(-0.1);
		ptr->player.vect_y = vect_x * sin(-0.1) + vect_y * cos(-0.1);
	}
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
	ptr.player.vect_y = -2;
	ptr.player.vect_x = 0;
	ptr.mlx = mlx_init();
 	ptr.win = mlx_new_window(ptr.mlx, ptr.info_file.res_x, ptr.info_file.res_y, "Window test");
	//ptr.img = mlx_new_image(ptr.mlx, 100, 100);
	//mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img, ptr.player.pos_x, ptr.player.pos_y);
	display_map(&ptr);
	display_player(&ptr);
	mlx_key_hook(ptr.win, key_quit, &ptr);
	mlx_hook(ptr.win, 2, 1L<<0, key_move, &ptr);
	mlx_loop(ptr.mlx);
	free_tab(ptr.info_file.file);
	return (0);
}