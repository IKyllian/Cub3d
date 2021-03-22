/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_minimap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 13:45:12 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/22 13:56:17 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	put_pixel(char c, int x, int y, t_window *ptr)
{
	if (c == '1')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 153, 51));
	else if (c == '2')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 0, 0, 255));
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 0, 153, 73));
	else if (c == '0')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 255, 255));
	else if (c == 'p')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 0));
	else if (c == 'v')
		my_mlx_pixel_put(ptr, x, y, ft_trgb(0, 255, 0, 255));
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
	my_mlx_pixel_put(ptr, vect_x * ratio, vect_y * ratio, ft_trgb(0,255, 0, 255));
	my_mlx_pixel_put(ptr, vect_x * ratio - 1, vect_y * ratio, ft_trgb(0,255, 0, 255));
	my_mlx_pixel_put(ptr, vect_x * ratio, vect_y * ratio - 1, ft_trgb(0,255, 0, 255));
	my_mlx_pixel_put(ptr, vect_x * ratio + 1, vect_y * ratio, ft_trgb(0,255, 0, 255));
	my_mlx_pixel_put(ptr, vect_x * ratio, vect_y * ratio + 1, ft_trgb(0,255, 0, 255));
}
