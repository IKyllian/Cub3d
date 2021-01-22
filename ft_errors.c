/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 15:52:34 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_wall_map(int error)
{
	if (error == 1)
		printf("Error\nLa map doit être fermée.\n");
	else if (error == 2)
		printf("Error\nIl ne peut y avoir que une position de depart.\n");
	else if (error == 3)
		printf("Error\nIl doit y avoir au moins une position de depart.\n");
	else if (error == 4)
		printf("Error\nErreur d'allocation.\n");
	exit(1);
}	