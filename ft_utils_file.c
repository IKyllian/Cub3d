/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/25 12:28:14 by kdelport         ###   ########lyon.fr   */
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

void	fill_tab(t_info_file *elem_f)
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
			if (elem_f->map_index < 0)
				elem_f->map_index = i;
			elem_f->map_size += 1;
		}
		elem_f->file[i++] = line;
	}
	elem_f->file[i] = NULL;
}

int		parse_file(t_info_file *elem_f)
{
	int		i;
	int		j;
	char	**str;

	i = -1;
	str = elem_f->file;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			while (str[i][j] == ' ')
				j++;
			if (str[i][j] == 'N' && str[i][j + 1] == 'O' && !elem_f->t_no)
				get_info_texture(str[i] + j, elem_f);
			else if (str[i][j] == 'S' && str[i][j + 1] == 'O' && !elem_f->t_so)
				get_info_texture(str[i] + j, elem_f);
			else if (str[i][j] == 'W' && str[i][j + 1] == 'E' && !elem_f->t_we)
				get_info_texture(str[i] + j, elem_f);
			else if (str[i][j] == 'E' && str[i][j + 1] == 'A' && !elem_f->t_ea)
				get_info_texture(str[i] + j, elem_f);
			else if (str[i][j] == 'R' && elem_f->res_x < 0 && elem_f->res_y < 0)
				get_color_res(str[i] + j, elem_f);
			else if (str[i][j] == 'S' && !elem_f->sprite)
				get_color_res(str[i] + j, elem_f);
			else if (str[i][j] == 'F' && elem_f->res_x)
				get_color_res(str[i] + j, elem_f);
			else if (str[i][j] == 'C' && elem_f->res_x)
				get_color_res(str[i] + j, elem_f);
		}
	}
	printf("Val N = %s\n", elem_f->t_no);
	printf("Val S = %s\n", elem_f->t_so);
	printf("Val E = %s\n", elem_f->t_ea);
	printf("Val W = %s\n", elem_f->t_we);
	printf("Val Sprite = %s\n", elem_f->sprite);
	printf("Val coord = %i - %i\n", elem_f->res_x, elem_f->res_y);
	printf("Val Ground = %i\n", elem_f->ground);
	printf("Val Ceiling = %i\n", elem_f->ceiling);
	return (0);
}
