/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/02/23 13:53:18 by kdelport         ###   ########lyon.fr   */
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

int		parse_file(t_window *ptr)
{
	int		i;
	int		j;
	char	**str;
	char	c;

	i = -1;
	str = ptr->info_file.file;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			while (str[i][j] == ' ')
				j++;
			c = str[i][j];
			if (c == 'N' && str[i][j + 1] == 'O' && !ptr->info_file.t_no)
				get_info_texture(str[i] + j, ptr);
			else if (c == 'S' && str[i][j + 1] == 'O' && !ptr->info_file.t_so)
				get_info_texture(str[i] + j, ptr);
			else if (c == 'W' && str[i][j + 1] == 'E' && !ptr->info_file.t_we)
				get_info_texture(str[i] + j, ptr);
			else if (c == 'E' && str[i][j + 1] == 'A' && !ptr->info_file.t_ea)
				get_info_texture(str[i] + j, ptr);
			else if (c == 'R' && ptr->info_file.res_x < 0 && ptr->info_file.res_y < 0)
				get_color_res(str[i] + j, ptr);
			else if (c == 'S' && !ptr->info_file.sprite)
				get_color_res(str[i] + j, ptr);
			else if (c == 'F' && ptr->info_file.res_x)
				get_color_res(str[i] + j, ptr);
			else if (c == 'C' && ptr->info_file.res_x)
				get_color_res(str[i] + j, ptr);
		}
	}
	printf("Val N = %s\n", ptr->info_file.t_no);
	printf("Val S = %s\n", ptr->info_file.t_so);
	printf("Val E = %s\n", ptr->info_file.t_ea);
	printf("Val W = %s\n", ptr->info_file.t_we);
	printf("Val Sprite = %s\n", ptr->info_file.sprite);
	printf("Val Res = %i - %i\n", ptr->info_file.res_x, ptr->info_file.res_y);
	printf("Val Ground = %i\n", ptr->info_file.ground);
	printf("Val Ceiling = %i\n", ptr->info_file.ceiling);
	return (0);
}
