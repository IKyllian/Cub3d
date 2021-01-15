/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:38:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/15 10:54:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx/mlx.h"

int main()
{
	void *connection;
	
	connection = mlx_init();
	mlx_new_window(connection, 900, 900, "Window test");
}