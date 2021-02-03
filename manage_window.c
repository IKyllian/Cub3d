/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:50:53 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/03 13:47:09 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_collision(float pos_x, float pos_y, t_window *ptr)
{
	char **map;
	int pos_y_cast;
	int pos_x_cast;

	pos_y_cast = (int)pos_y;
	pos_x_cast = (int)pos_x;
	map = ptr->info_file.file + ptr->info_file.map_index;
	if ((pos_y >= 0 || pos_y_cast < ptr->info_file.map_size ||
		pos_y_cast < ft_strlen(map[(int)ptr->player.pos_y])) &&
		map[pos_y_cast][pos_x_cast] != '1' &&
		map[pos_y_cast][pos_x_cast] != '2') //Check Collision
		return (0);
	return (1);
}

int		key_quit(int keycode, t_window *ptr)
{
	(void)ptr;
	if (keycode == 53)
		exit(0);
	return (0);
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
	if ((keycode == 13 || keycode == 126) && !is_collision(x + vect_x * 0.1, y + vect_y * 0.1, ptr)) // Touche w et fleche haut
	{
		ptr->player.pos_x = x + vect_x * 0.1;
		ptr->player.pos_y = y + vect_y * 0.1;
	}
	else if ((keycode == 1 || keycode == 125) && !is_collision(x - vect_x * 0.1, y - vect_y * 0.1, ptr)) // Touche s et fleche bas
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

void	create_window(t_window *ptr)
{
	ptr->mlx = mlx_init();
 	ptr->win = mlx_new_window(ptr->mlx, ptr->info_file.res_x, ptr->info_file.res_y, "Window test");
	//ptr->img = mlx_new_image(ptr->mlx, 100, 100);
	//mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img, ptr->player.pos_x, ptr->player.pos_y);
	display_map(ptr);
	display_player(ptr);
	mlx_key_hook(ptr->win, key_quit, ptr);
	mlx_hook(ptr->win, 2, 1L<<0, key_move, ptr);
	mlx_loop(ptr->mlx);
}