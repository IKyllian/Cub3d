/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:20:46 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 16:15:45 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char *str;

	str = (char *)s;
	while (n--)
		*str++ = (unsigned char)c;
	return (s);
}
