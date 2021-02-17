/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:45:12 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/15 11:44:34 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		put_pixel(char c, int x, int y, t_window *ptr)
{
	if (c == '1')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 255, 153, 51));
	else if (c == '2')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 0, 0, 255));
	else if (c == 'N' || c == 'S' || c == 'E' ||c == 'W')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 0, 153, 73));
	else if (c == '0')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 255, 255, 255));
	else if (c == 'p')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0, 255, 0, 0));
	else if (c == 'v')
		mlx_pixel_put(ptr->mlx, ptr->win, x, y, ft_trgb(0,255, 0, 255));
	return (0);
}

void	display_map(t_window *ptr)
{
	int y;
	int x;
	char **map;
	int ratio;

	y = -1;
	ratio = ptr->ratio;
	map = ptr->info_file.file + ptr->info_file.map_index;
	while (++y / ratio < ptr->info_file.map_size)
	{
		x = -1;
		while (++x / ratio < ft_strlen(map[y / ratio]) && map[y / ratio][x / ratio])
			put_pixel(map[y / ratio][x / ratio], x, y, ptr);
	}
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
	
	put_pixel('p', x, y, ptr);
	put_pixel('p', x - 1, y, ptr);
	put_pixel('p', x, y - 1, ptr);
	put_pixel('p', x + 1, y, ptr);
	put_pixel('p', x, y + 1, ptr);

	put_pixel('v', vect_x * ratio, vect_y * ratio, ptr);
	put_pixel('v', vect_x * ratio - 1, vect_y * ratio, ptr);
	put_pixel('v', vect_x * ratio, vect_y * ratio - 1, ptr);
	put_pixel('v', vect_x * ratio + 1, vect_y * ratio, ptr);
	put_pixel('v', vect_x * ratio, vect_y * ratio + 1, ptr);
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
	put_pixel(map[y / ratio][x / ratio], x, y, ptr);
	put_pixel(map[y / ratio][(int)((x - 1) / ratio)], x - 1, y, ptr);
	put_pixel(map[(int)((y - 1) / ratio)][x / ratio], x, y - 1, ptr);
	put_pixel(map[y / ratio][(int)((x + 1) / ratio)], x + 1, y, ptr);
	put_pixel(map[(int)((y + 1) / ratio)][x / ratio], x, y + 1, ptr);
}


void	remove_vecteur(t_window *ptr, int index_x, int index_y)
{
	char **map = ptr->info_file.file + ptr->info_file.map_index;
	int vect_x;
	int vect_y;
	int ratio;

	ratio = ptr->ratio;
	vect_x = (ptr->player.pos_x +  ptr->player.vect_x) * ratio;
	vect_y = (ptr->player.pos_y + ptr->player.vect_y) * ratio;
	if ((index_y >= 0 && index_y < ptr->info_file.map_size) && (index_x >= 0 && index_x < ptr->info_file.map_width))
		put_pixel(map[index_y][index_x], vect_x, vect_y, ptr);
	if ((index_y >= 0 && index_y < ptr->info_file.map_size) && (index_x >= 0 && index_x < ptr->info_file.map_width))
		put_pixel(map[index_y][index_x], vect_x - 1, vect_y, ptr);
	if ((index_y >= 0 && index_y< ptr->info_file.map_size) && (index_x >= 0 && index_x < ptr->info_file.map_width))
		put_pixel(map[index_y][index_x], vect_x, vect_y - 1, ptr);
	if ((index_y >= 0 && index_y < ptr->info_file.map_size) && (index_x >= 0 && index_x < ptr->info_file.map_width))
		put_pixel(map[index_y][index_x], vect_x + 1, vect_y, ptr);
	if ((index_y >= 0 && index_y < ptr->info_file.map_size) && (index_x >= 0 && index_x < ptr->info_file.map_width))
		put_pixel(map[index_y][index_x], vect_x, vect_y + 1, ptr);
}
