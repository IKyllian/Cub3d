/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 15:18:47 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:19:23 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_info_str(char *str, t_window *ptr, int is_sprite)
{
	int		i;
	char	*path;

	i = 0;
	str++;
	if (!is_sprite)
		str++;
	if (*str != 32 && *str != '\t')
		ft_error("L'identifiant doit etre suivis d'un espace", 1, ptr, 0);
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	if (*str == '\0')
		ft_error("Une ligne est incorrect dans le fichier", 1, ptr, 0);
	while (str[i] && (str[i] != ' ' || str[i] == '\t'))
		i++;
	if (str[i] != '\0')
		ft_error("Caractere en trop en fin de ligne", 1, ptr, 0);
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
		ft_error("L'identifiant doit etre suivis d'un espace", 1, ptr, 0);
	get_number(&str, ptr, &resx, 0);
	get_number(&str, ptr, &resy, 0);
	if (*str != '\0')
		ft_error("Il ne doit pas avoir de caratere apres les informations", \
			1, ptr, 0);
	if (resx <= 0 || resy <= 0)
		ft_error("La résolution doit être superieur à 0", 1, ptr, 0);
	if (resx > 2560)
		resx = 2560;
	if (resy > 1340)
		resy = 1340;
	ptr->info_file.res_x = resx;
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
		ft_error("L'identifiant doit etre suivis d'un espace", 1, ptr, 0);
	get_number(&str, ptr, &r, 0);
	get_number(&str, ptr, &g, 1);
	get_number(&str, ptr, &b, 1);
	if (*str != '\0')
		ft_error("Il ne doit pas avoir de caratere apres les informations", \
			1, ptr, 0);
	if (r > 255 || g > 255 || b > 255)
		ft_error("La valeur d'une des couleurs est superieur a 255", 1, ptr, 0);
	return (ft_trgb(0, r, g, b));
}

void	get_info_texture(char *str, t_window *ptr)
{
	if (*str == 'N' && !info_exist(ptr->info_file.t_no, -2, ptr))
		ptr->info_file.t_no = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == 'B'
		&& !info_exist(ptr->info_file.skybox, -2, ptr))
		ptr->info_file.skybox = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == 'O'
		&& !info_exist(ptr->info_file.t_so, -2, ptr))
		ptr->info_file.t_so = get_info_str(str, ptr, 0);
	else if (*str == 'E' && !info_exist(ptr->info_file.t_ea, -2, ptr))
		ptr->info_file.t_ea = get_info_str(str, ptr, 0);
	else if (*str == 'W' && !info_exist(ptr->info_file.t_we, -2, ptr))
		ptr->info_file.t_we = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == 'F'
		&& !info_exist(ptr->info_file.t_end_sprite, -2, ptr))
		ptr->info_file.t_end_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == '5'
		&& !info_exist(ptr->info_file.t_trap_sprite, -2, ptr))
		ptr->info_file.t_trap_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == '6'
		&& !info_exist(ptr->info_file.t_heal_sprite, -2, ptr))
		ptr->info_file.t_heal_sprite = get_info_str(str, ptr, 0);
	else if (*str == 'S' && str[1] == ' '
		&& !info_exist(ptr->info_file.t_sprite, -2, ptr))
		ptr->info_file.t_sprite = get_info_str(str, ptr, 1);
}

void	get_info_sprite(char *str, t_window *ptr)
{
	if (*str == 'R' && !info_exist(NULL, ptr->info_file.res_x, ptr)
		&& !info_exist(NULL, ptr->info_file.res_y, ptr))
		get_info_coord(str, ptr);
	else if (*str == 'F' && !info_exist(NULL, ptr->info_file.ground, ptr))
		ptr->info_file.ground = get_info_color(str, ptr);
	else if (*str == 'C' && !info_exist(NULL, ptr->info_file.ceiling, ptr))
		ptr->info_file.ceiling = get_info_color(str, ptr);
}
