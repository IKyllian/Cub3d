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

int		key_quit(int keycode, t_window *ptr)
{
	(void)ptr;
	if (keycode == 53)
		exit(0);
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