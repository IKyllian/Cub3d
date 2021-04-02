/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 10:42:34 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/02 10:56:11 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	shader(t_window *ptr)
{
	int		i;
	float	x;
	float	j;
	float	step;

	i = 0;
	x = 0;
	j = 0;
	step = ptr->info_file.res_y / 510;
	while (i < ptr->info_file.res_y / 2)
	{
		ptr->fov.shade[i] = trgbmod(ptr->info_file.ceiling, 1 - j * 0.0005);
		if (i++ % (ptr->info_file.res_y) / 10 == 0)
			x += 0.17;
		j += step * x;
	}
	while (i < ptr->info_file.res_y)
	{
		ptr->fov.shade[i] = trgbmod(ptr->info_file.ground, 1 - j * 0.0005);
		if (i++ % (ptr->info_file.res_y) / 10 == 0)
			x -= 0.17;
		j -= step * x;
	}
	while (i < ptr->info_file.res_y + 80)
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
	r *= factor;
	if (r <= 0)
		r = 0;
	if (r > 256)
		r = 255;
	g *= factor;
	if (g <= 0)
		g = 0;
	if (g > 256)
		g = 255;
	b *= factor;
	if (b <= 0)
		b = 0;
	if (b > 256)
		b = 255;
	return (ft_trgb(t, r, g, b));
}