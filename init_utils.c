/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 13:28:38 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:12:02 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_array_file(t_info_file *elem_f)
{
	elem_f->t_no = NULL;
	elem_f->t_so = NULL;
	elem_f->t_we = NULL;
	elem_f->t_ea = NULL;
	elem_f->t_sprite = NULL;
	elem_f->t_end_sprite = NULL;
	elem_f->t_trap_sprite = NULL;
	elem_f->t_heal_sprite = NULL;
	elem_f->skybox = NULL;
	elem_f->cpy_map = NULL;
	elem_f->file = NULL;
	elem_f->map = NULL;
}

int	info_exist(char *str, int nbr, t_window *ptr)
{
	if (nbr == -2)
	{
		if (str)
			ft_error("Un parametre de config est en double", 1, ptr, 0);
	}
	else
	{
		if (nbr > 0)
			ft_error("Un parametre de config est en double", 1, ptr, 0);
	}
	return (0);
}
