/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:21:38 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 12:22:20 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	step_init(float cam, float start, float pl)
{
	if (cam >= 0)
		return ((int)start + 1);
	else if (start == pl)
		return ((int)start);
	else
		return ((int)start - 1);
}