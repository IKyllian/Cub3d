/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:31:07 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/20 14:43:38 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *source)
{
	int		i;
	char	*str;

	if (!(str = (char *)malloc(sizeof(*str) * (ft_strlen(source) + 1))))
		return (NULL);
	i = 0;
	while (source[i])
	{
		str[i] = source[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
