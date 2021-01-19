/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/19 16:15:42 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}


char 	*get_info_str(char *str, t_info_file *elem_f)
{
	int i;
	char *path;

	i = 0;
	str += 2;
	while (*str && *str == ' ')
		str++;
	while (str[i] && str[i++] != ' ')
		i++;
	if (!(path = malloc(sizeof(char) * (i + 1))))
		return NULL;
	i = 0;
	while (*str && *str != ' ')
		path[i++] = *str++;
	path[i] = 0;
	return (path);
}

void	get_info_coord(char *str, t_info_file *elem_f)
{
	int nb;

	nb = 0;
	str++;
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		nb = nb * 10 + (*str++ - 48);
	elem_f->res_x = nb;
	nb = 0;
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		nb = nb * 10 + (*str++ - 48);
	elem_f->res_y = nb;
}

int		get_info_color(char *str, t_info_file *elem_f)
{
	int r;
	int g;
	int b;

	r = 0;
	g = 0;
	b = 0;
	str++;
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		r = r * 10 + (*str++ - 48);
	if (*str == ',')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		g = g * 10 + (*str++ - 48);
	if (*str == ',')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		b = b * 10 + (*str++ - 48);
	return (create_trgb(0, r, g, b));
}

void	get_info_texture(char *str, t_info_file *elem_f)
{
	
	if (*str == 'N')
		elem_f->t_no = get_info_str(str, elem_f);
	else if (*str == 'S')
		elem_f->t_so = get_info_str(str, elem_f);
	else if (*str == 'E')
		elem_f->t_ea = get_info_str(str, elem_f);
	else if (*str == 'W')
		elem_f->t_we = get_info_str(str, elem_f);
	printf("Val N = %s\n", elem_f->t_no);
	printf("Val S = %s\n", elem_f->t_so);
	printf("Val E = %s\n", elem_f->t_ea);
	printf("Val W = %s\n", elem_f->t_we);
}

void	get_color_res(char *str, t_info_file *elem_f)
{
	if (*str == 'R')
		get_info_coord(str, elem_f);
	else if (*str == 'S')
		elem_f->sprite = get_info_str(str, elem_f);
	else if (*str == 'F')
		elem_f->ground = get_info_color(str, elem_f);
	else if (*str == 'C')
		elem_f->ceiling = get_info_color(str, elem_f);
	printf("Val Sprite = %s\n", elem_f->sprite);
	printf("Val coord = %i - %i\n", elem_f->res_x, elem_f->res_y);
	printf("Val Ground = %i\n", elem_f->ground);
	printf("Val Ceiling = %i\n", elem_f->ceiling);
}