/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:42:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 13:22:44 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shader(t_window *ptr)
{
	int		i;
	float	j;
	float	step;

	i = 0;
	j = 0;
	step = ptr->info_file.res_y / 510;
	while (i < ptr->info_file.res_y / 2)
	{
		ptr->fov.shade[i] = trgbmod(ptr->info_file.ceiling, 0 + j * 0.0007);
		j += step;
		i++;
	}
	while (i < ptr->info_file.res_y)
	{
		ptr->fov.shade[i] = trgbmod(ptr->info_file.ground, 0 + j * 0.0007);
		j -= step;
		i++;
	}
	while (i < (int)(ptr->info_file.res_y * 8))
		ptr->fov.shade[i++] = ptr->info_file.ground;
}

int	trgbmod(int trgb, float factor)
{
	int		t;
	int		r;
	int		g;
	int		b;

	t = trgb & (255 << 24);
	r = (trgb & (255 << 16)) / 65536;
	g = (trgb & (255 << 8)) / 256;
	b = trgb & (255);
	r += factor * 50;
	if (r >= 256)
		r = 255;
	if (r <= 0)
		r = 0;
	g += factor * 50;
	if (g >= 256)
		g = 255;
	if (g <= 0)
		g = 0;
	b += factor * 50;
	if (b >= 256)
		b = 255;
	if (b <= 0)
		b = 0;
	return (ft_trgb(t, r, g, b));
}
