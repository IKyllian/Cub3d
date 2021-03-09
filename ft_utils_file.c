/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/09 11:20:16 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		line_is_map(char *line)
{
	if ((*line >= 48 && *line <= 57) || *line == ' ' || *line == '\t')
		return (1);
	return (0);
	//Ne gere pas si une ligne contient uniquement des espaces ou des tabs
}

int		get_file_size(void)
{
	int		fd;
	int		ret;
	int		size;
	char	*line;

	size = 0;
	fd = open("text.cub", O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		size++;
	}
	close(fd);
	return (size);
}

void	fill_tab(t_window *ptr)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	i = 0;
	fd = open("text.cub", O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line_is_map(line))
		{
			if (ptr->info_file.map_index < 0)
				ptr->info_file.map_index = i;
			ptr->info_file.map_size += 1;
		}
		ptr->info_file.file[i++] = line;
	}
	ptr->info_file.file[i] = NULL;
	ptr->info_file.map = ptr->info_file.file + ptr->info_file.map_index;
}

int		file_is_valid(t_window *ptr)
{
	if (!ptr->info_file.t_no || !ptr->info_file.t_so || !ptr->info_file.t_we ||
		!ptr->info_file.t_ea || (ptr->info_file.res_x < 0 &&
		ptr->info_file.res_y < 0) || !ptr->info_file.t_sprite ||
		ptr->info_file.ground < 0 || ptr->info_file.ceiling < 0)
		return (0);
	else
		return (1);
}

void	check_letters(t_window *ptr, char *str)
{
	if (str[0] == 'N' && ft_strlen(str) >= 2 && str[1] == 'O')
		get_info_texture(str, ptr);
	else if (str[0] == 'S' && ft_strlen(str) >= 2 && str[1] == 'O')
		get_info_texture(str, ptr);
	else if (str[0] == 'W' && ft_strlen(str) >= 2 && str[1] == 'E')
		get_info_texture(str, ptr);
	else if (str[0] == 'E' && ft_strlen(str) >= 2 && str[1] == 'A')
		get_info_texture(str, ptr);
	else if (str[0] == 'R')
		get_color_res(str, ptr);
	else if (str[0] == 'S')
		get_color_res(str, ptr);
	else if (str[0] == 'F')
		get_color_res(str, ptr);
	else if (str[0] == 'C')
		get_color_res(str, ptr);
}

int		parse_file(t_window *ptr)
{
	int		i;
	char	**str;

	i = -1;
	str = ptr->info_file.file;
	while (str[++i] && i < ptr->info_file.map_index)
		check_letters(ptr, str[i]);
	if (!file_is_valid(ptr))
		return (-1);
	// printf("Val N = %s\n", ptr->info_file.t_no);
	// printf("Val S = %s\n", ptr->info_file.t_so);
	// printf("Val E = %s\n", ptr->info_file.t_ea);
	// printf("Val W = %s\n", ptr->info_file.t_we);
	// printf("Val Sprite = %s\n", ptr->info_file.t_sprite);
	// printf("Val Res = %i - %i\n", ptr->info_file.res_x, ptr->info_file.res_y);
	// printf("Val Ground = %i\n", ptr->info_file.ground);
	// printf("Val Ceiling = %i\n", ptr->info_file.ceiling);
	return (0);
}
