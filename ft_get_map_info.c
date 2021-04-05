/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_map_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/05 13:51:12 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_info_str(char *str, t_window *ptr, int is_sprite)
{
	int		i;
	char	*path;

	i = 0;
	if (is_sprite)
		str++;
	else
		str += 2;
	if (*str != 32 && *str != '\t')
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '\0')
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr);
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		i++;
	if (str[i] != '\0')
		ft_error("Il ne doit pas avoir de caratere apres les informations", \
			1, ptr);
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
	int	resx;
	int	resy;

	resx = 0;
	resy = 0;
	str++;
	if (*str != 32 && *str != '\t')
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr);
	get_number(&str, ptr, &resx, 0);
	get_number(&str, ptr, &resy, 0);
	if (*str != '\0')
		ft_error("Il ne doit pas avoir de caratere apres les informations", \
			1, ptr);
	if (resx > 2560)
		ptr->info_file.res_x = 2560;
	else
		ptr->info_file.res_x = resx;
	if (resy > 1440)
		ptr->info_file.res_y = 1440;
	else
		ptr->info_file.res_y = resy;
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
	if (*str != 32 && *str != '\t')
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr);
	get_number(&str, ptr, &r, 0);
	get_number(&str, ptr, &g, 1);
	get_number(&str, ptr, &b, 1);
	if (*str != '\0')
		ft_error("Il ne doit pas avoir de caratere apres les informations", \
			1, ptr);
	if (r > 255 || g > 255 || b > 255)
		ft_error("La valeur d'une des couleurs est superieur a 255", 1, ptr);
	return (ft_trgb(0, r, g, b));
}

void	get_info_texture(char *str, t_window *ptr)
{
	if (*str == 'N' && !info_exist(ptr->info_file.t_no, -2, ptr))
		ptr->info_file.t_no = get_info_str(str, ptr, 0);
	else if (*str == 'S' && !info_exist(ptr->info_file.t_so, -2, ptr))
		ptr->info_file.t_so = get_info_str(str, ptr, 0);
	else if (*str == 'E' && !info_exist(ptr->info_file.t_ea, -2, ptr))
		ptr->info_file.t_ea = get_info_str(str, ptr, 0);
	else if (*str == 'W' && !info_exist(ptr->info_file.t_we, -2, ptr))
		ptr->info_file.t_we = get_info_str(str, ptr, 0);
}

void	get_color_res(char *str, t_window *ptr)
{
	if (*str == 'R' && !info_exist(NULL, ptr->info_file.res_x, ptr)
		&& !info_exist(NULL, ptr->info_file.res_y, ptr))
		get_info_coord(str, ptr);
	else if (*str == 'S' && str[1] == '4'
		&& !info_exist(ptr->info_file.t_second_sprite, -2, ptr))
		ptr->info_file.t_second_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == '5'
		&& !info_exist(ptr->info_file.t_trap_sprite, -2, ptr))
		ptr->info_file.t_trap_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == '6'
		&& !info_exist(ptr->info_file.t_heal_sprite, -2, ptr))
		ptr->info_file.t_heal_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && !info_exist(ptr->info_file.t_sprite, -2, ptr))
		ptr->info_file.t_sprite = get_info_str(str, ptr, 1);
	else if (*str == 'F' && !info_exist(NULL, ptr->info_file.ground, ptr))
		ptr->info_file.ground = get_info_color(str, ptr);
	else if (*str == 'C' && !info_exist(NULL, ptr->info_file.ceiling, ptr))
		ptr->info_file.ceiling = get_info_color(str, ptr);
}
