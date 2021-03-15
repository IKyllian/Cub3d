/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:55:04 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/15 13:36:11 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	anglizer(float vx1, float vy1, float vx2, float vy2)
{
	float	determinant;

	determinant = vx1 * vy2 - vx2 * vy1;
	if (determinant >= 0)
		return (1);
	else
		return (-1);
}
