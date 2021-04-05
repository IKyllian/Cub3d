/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:50:53 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/05 14:38:49 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_window(t_window *ptr)
{
	ft_error("\0", 0, ptr);
	return (0);
}

void	create_window(t_window *ptr)
{
	ptr->mlx = mlx_init();
	if (!ptr->save)
		ptr->win = mlx_new_window(ptr->mlx, ptr->info_file.res_x,
				ptr->info_file.res_y, "cub3D");
	create_text_struct(ptr);
	if (ptr->info_file.nb_sprite > 0)
		sprite_init(ptr);
	img_init(ptr);
	if (!ptr->save)
	{
		mlx_hook(ptr->win, 2, 1L << 0, key_press, ptr);
		mlx_hook(ptr->win, 3, 1L << 1, key_release, ptr);
		mlx_hook(ptr->win, 17, 1L << 17, exit_window, ptr);
	}
	mlx_loop_hook(ptr->mlx, frame_gen, ptr);
	mlx_loop(ptr->mlx);
}
