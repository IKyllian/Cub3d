/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:28:38 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 14:29:32 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	info_exist(char *str, int nbr, t_window *ptr)
{
	if (nbr == -2)
	{
		if (str)
			ft_error(7, ptr);
	}
	else
	{
		if (nbr > 0)
			ft_error(7, ptr);
	}
	return (0);
}
