/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 11:35:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/22 16:13:22 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc(size_t element_count, size_t element_size)
{
	void	*mem;

	if (!(mem = malloc(element_size * element_count)))
		return (NULL);
	ft_memset(mem, 0, element_count * element_size);
	return (mem);
}
