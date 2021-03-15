/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:04:09 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/15 12:50:01 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	map_is_valid(char **map, int size)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		if (i == 0 || i == size - 1)
		{
			while (map[i][++j])
				if ((map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' '))
					return (0);
		}
		else
		{
			while (map[i][++j])
				if ((j == 0 || map[i][j + 1] == ' ') && \
					(map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' '))
					return (0);
		}
	}
	return (1);
}
