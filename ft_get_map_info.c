/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/19 10:38:41 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_info_str(char *str)
{
	int		i;
	char	*path;

	i = 0;
	str += 2;
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		i++;
	path = malloc(sizeof(char) * (i + 1));
	if (!path)
		return (NULL);
	i = 0;
	while (*str && *str != ' ')
		path[i++] = *str++;
	path[i] = 0;
	return (path);
}

void	get_info_coord(char *str, t_window *ptr)
{
	int	nb;

	nb = 0;
	str++;
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		nb = nb * 10 + (*str++ - 48);
	ptr->info_file.res_x = nb;
	nb = 0;
	while (*str && *str == ' ')
		str++;
	while (*str && (*str >= 48 && *str <= 57))
		nb = nb * 10 + (*str++ - 48);
	ptr->info_file.res_y = nb;
}

void	get_number(char **str, t_window *ptr, int *color)
{
	while (*(*str) && (*(*str) == ',' || *(*str) == ' '))
		(*str)++;
	if (*(*str) < 48 || *(*str) > 57)
		ft_error(8, ptr);
	while (*(*str) && (*(*str) >= 48 && *(*str) <= 57))
		*color = *color * 10 + (*(*str)++ - 48);
}

int	get_info_color(char *str, t_window *ptr)
{
	int	r;
	int	g;
	int	b;

	r = 0;
	g = 0;
	b = 0;
	str++;
	get_number(&str, ptr, &r);
	get_number(&str, ptr, &g);
	get_number(&str, ptr, &b);
	// while (*str && *str == ' ')
	// 	str++;
	// while (*str && (*str >= 48 && *str <= 57))
	// 	r = r * 10 + (*str++ - 48);
	// while (*str == ',' || *str == ' ')
	// 	str++;
	// while (*str && (*str >= 48 && *str <= 57))
	// 	g = g * 10 + (*str++ - 48);
	// while (*str == ',' || *str == ' ')
	// 	str++;
	// while (*str && (*str >= 48 && *str <= 57))
	// 	b = b * 10 + (*str++ - 48);
	if (r > 255 || g > 255 || b > 255)
		ft_error(10, ptr);
	return (ft_trgb(0, r, g, b));
}

void	get_info_texture(char *str, t_window *ptr)
{
	if (*str == 'N' && !info_exist(ptr->info_file.t_no, -2, ptr))
		ptr->info_file.t_no = get_info_str(str);
	else if (*str == 'S' && !info_exist(ptr->info_file.t_so, -2, ptr))
		ptr->info_file.t_so = get_info_str(str);
	else if (*str == 'E' && !info_exist(ptr->info_file.t_ea, -2, ptr))
		ptr->info_file.t_ea = get_info_str(str);
	else if (*str == 'W' && !info_exist(ptr->info_file.t_we, -2, ptr))
		ptr->info_file.t_we = get_info_str(str);
}

void	get_color_res(char *str, t_window *ptr)
{
	if (*str == 'R' && !info_exist(NULL, ptr->info_file.res_x, ptr)
		&& !info_exist(NULL, ptr->info_file.res_y, ptr))
		get_info_coord(str, ptr);
	else if (*str == 'S' && !info_exist(ptr->info_file.t_sprite, -2, ptr))
		ptr->info_file.t_sprite = get_info_str(str);
	else if (*str == 'F' && !info_exist(NULL, ptr->info_file.ground, ptr))
		ptr->info_file.ground = get_info_color(str, ptr);
	else if (*str == 'C' && !info_exist(NULL, ptr->info_file.ceiling, ptr))
		ptr->info_file.ceiling = get_info_color(str, ptr);
}