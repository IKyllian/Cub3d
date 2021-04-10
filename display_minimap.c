/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:45:12 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/10 13:32:22 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_pixel(char c, int x, int y, t_window *ptr)
{
	if (c == '1')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 153, 51));
	else if (c == '2' || c == '4' || c == '5' || c == '6')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 0, 0, 255));
	else if (c == '3')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 204, 102, 0));
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 0, 153, 73));
	else if (c == '0')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 255, 255));
	else if (c == 'p')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 0));
	else if (c == 'v')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 255));
	else if (c == 'h')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 204, 0, 102));
	return (0);
}

void	display_map(t_window *ptr)
{
	int		y;
	int		x;
	char	**map;
	int		ratio;

	y = -1;
	ratio = ptr->ratio;
	map = ptr->info_file.map;
	while (++y / ratio < ptr->info_file.map_size)
	{
		x = -1;
		while (++x / ratio < ft_strlen(map[y / ratio])
			&& map[y / ratio][x / ratio])
			put_pixel(map[y / ratio][x / ratio], x, y, ptr);
	}
}

void	display_hp(t_window *ptr)
{
	int		y;
	int		x;
	int		life_height;
	char	**map;

	y = ptr->info_file.res_y - 4;
	life_height = 45;
	map = ptr->info_file.map;
	if (ptr->info_file.res_y < 150)
		life_height = 10;
	else if (ptr->info_file.res_y < 500)
		life_height = 25;
	while (--y > ptr->info_file.res_y - life_height)
	{
		x = 4;
		while (++x < ptr->player.life_bar)
		{
			if (ptr->player.health >= 50)
				my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 0, 204, 102));
			else if (ptr->player.health < 50 && ptr->player.health > 25)
				my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 153, 51));
			else
				my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 0));
		}
	}
}

void	display_player(t_window *ptr)
{
	int		x;
	int		y;
	int		ratio;
	float	vect_x;
	float	vect_y;

	vect_x = ptr->player.pos_x + ptr->fov.vect_x;
	vect_y = ptr->player.pos_y + ptr->fov.vect_y;
	ratio = ptr->ratio;
	x = ptr->player.pos_x * ratio;
	y = ptr->player.pos_y * ratio;
	my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 0));
	my_mlx_pixel_put(ptr, x - 1, y, ft_trgb(0, 255, 0, 0));
	my_mlx_pixel_put(ptr, x, y - 1, ft_trgb(0, 255, 0, 0));
	my_mlx_pixel_put(ptr, x + 1, y, ft_trgb(0, 255, 0, 0));
	my_mlx_pixel_put(ptr, x, y + 1, ft_trgb(0, 255, 0, 0));
}
