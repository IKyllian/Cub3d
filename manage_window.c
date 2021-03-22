/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:50:53 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/22 14:04:58 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	key_quit(int keycode, t_window *ptr)
// {
// 	(void)ptr;
// 	if (keycode == 53)
// 		ft_error(100, ptr);
// 	return (0);
// }

void	create_window(t_window *ptr)
{
	ptr->mlx = mlx_init();
	if (!ptr->save)
		ptr->win = mlx_new_window(ptr->mlx, ptr->info_file.res_x,
				ptr->info_file.res_y, "cub3D");
	create_text_struct(ptr);
	sprite_init(ptr);
	img_init(ptr);
	if (!ptr->save)
	{
		mlx_hook(ptr->win, 2, 1L << 0, key_press, ptr);
		mlx_hook(ptr->win, 3, 1L << 1, key_release, ptr);
	}
	mlx_loop_hook(ptr->mlx, frame_gen, ptr);
	mlx_loop(ptr->mlx);
}
