/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:38:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/25 10:58:20 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



// int		create_trgb(int t, int r, int g, int b)
// {
// 	return(t << 24 | r << 16 | g << 8 | b);
// }

// int		key_pressed(int keycode, t_struct *ptr)
// {
// 	if (keycode == 53)
// 		exit(0);
// 	return (0);
// }

// int		ft_on_click(int button, int x, int y, t_struct *ptr)
// {
// 	ptr->is_press = 1;
// 	return (0);
// }

// int		ft_on_release(int button, int x, int y, t_struct *ptr)
// {
// 	ptr->is_press = 0;
// 	return (0);
// }


// int		ft_paint(int x, int y, t_struct *ptr)
// {
// 	if (ptr->is_press)
// 		mlx_pixel_put(ptr->mlx, ptr->win, x, y, create_trgb(0, 248, 123, 9));

// 	return (0);
// }

// void	open_window(t_info_file *elem_f)
// {

// }

// int main()
// {
// 	t_struct *ptr;
	
// 	ptr = malloc(sizeof(t_struct));
// 	ptr->mlx = mlx_init();
// 	ptr->win = mlx_new_window(ptr->mlx, 1000, 1000, "Window test");
// 	ptr->is_press = 0;
// 	mlx_key_hook(ptr->win, key_pressed, ptr);
// 	mlx_hook(ptr->win, 4, 1L<<2, ft_on_click, ptr);
// 	mlx_hook(ptr->win, 5, 1L<<3, ft_on_release, ptr);
// 	mlx_hook(ptr->win, 6, 1L<<6, ft_paint, ptr);
// 	mlx_loop(ptr->mlx);
// }