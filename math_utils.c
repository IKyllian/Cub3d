/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:55:04 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/22 14:05:11 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist_calc(float x, float y)
{
	return (sqrtf(powf(x, 2) + powf(y, 2)));
}

float	ft_dist(float x1, float y1, float x2, float y2)
{
	return (sqrtf(powf(x2 - x1, 2) + powf(y2 - y1, 2)));
}

int	anglizer(float vx1, float vy1, float vx2, float vy2)
{
	float	determinant;

	determinant = vx1 * vy2 - vx2 * vy1;
	if (determinant >= 0)
		return (1);
	else
		return (-1);
}

float	rad_deg(float rad)
{
	return (rad * 180 / M_PI);
}

float	deg_rad(float deg)
{
	return (deg * M_PI / 180);
}
