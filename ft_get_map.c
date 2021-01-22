/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:04:09 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 16:50:18 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int		map_is_valid(char **map, int size)
// {
// 	int i;
// 	int j;

// 	i = -1;
// 	while (map[++i])
// 	{
// 		j = -1;
// 		if (i == 0 || i == size - 1)
// 		{
// 			while (map[i][++j] && map[i][j] != ' ')
// 				if ((map[i][j] != '1' && map[i][j] != '0'))
// 					return (0);
// 		}
// 		else
// 		{
// 			if ((map[i][0] != '1' && map[i][0] != '0'))
// 				return (0);
// 			if ((map[i][ft_strlen(map[i]) - 1] != '1' &&
// 				map[i][ft_strlen(map[i]) - 1] != '0'))
// 				return (0);
// 		}
// 	}
// 	return (1);
// }


int		map_is_valid(char **map, int size)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		if (i == 0 || i == size - 1)
		{
			while (map[i][++j] && map[i][j] != ' ')
				if ((map[i][j] != '1' && map[i][j] != '0'))
					return (0);
		}
		else
		{
			while (map[i][++j] && map[i][j] != ' ')
				if ((j == 0 || j + 1 == ' ' ) && (map[i][j] != '1' && map[i][j] != '0'))
					return (0);
		}
	}
	return (1);
}
