/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/19 16:22:04 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_tab(char ***str)
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
		(*str)[i++] = line;
	}
	(*str)[i] = NULL;
}

int		parse_map(char **str)
{
	int i;
	int j;

	i = -1;
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			if (j == 0 && (str[i][j] != '1' && str[i][j] != ' '))
				return (-1);
			if ((j == ft_strlen(str[i]) - 1) && (str[i][j] != '1' && str[i][j] != ' '))
				return (-1);
			if (i == 0 && (str[i][j] != '1' && str[i][j] != ' '))
				return (-1);
			if (str[i + 1] == NULL && (str[i][j] != '1' && str[i][j] != ' '))
				return (-1);
		}
	}
	return (1);
}

void	init_struct(t_info_file *elem_f)
{
	elem_f->res_x = -1;
	elem_f->res_y = -1;
	elem_f->t_no = NULL;
	elem_f->t_so = NULL;
	elem_f->t_we = NULL;
	elem_f->t_ea = NULL;
	elem_f->sprite = NULL;
	elem_f->ground = -1;
	elem_f->ceiling = -1;
}

int		parse_file(char **str)
{
	int i;
	int j;
	t_info_file elem_f;

	i = -1;
	init_struct(&elem_f);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			while (str[i][j] == ' ')
				j++;
			if (str[i][j] == 'N' && str[i][j + 1] == 'O' && !elem_f.t_no)
				get_info_texture(str[i] + j, &elem_f);
			else if (str[i][j] == 'S' && str[i][j + 1] == 'O' && !elem_f.t_so)
				get_info_texture(str[i] + j, &elem_f);
			else if (str[i][j] == 'W' && str[i][j + 1] == 'E' && !elem_f.t_we)
				get_info_texture(str[i] + j, &elem_f);
			else if (str[i][j] == 'E' && str[i][j + 1] == 'A' && !elem_f.t_ea)
				get_info_texture(str[i] + j, &elem_f);
			else if (str[i][j] == 'R' && elem_f.res_x < 0 && elem_f.res_y < 0)
				get_color_res(str[i] + j, &elem_f);
			else if (str[i][j] == 'S' && !elem_f.sprite)
				get_color_res(str[i] + j, &elem_f);
			else if (str[i][j] == 'F' && elem_f.res_x)
				get_color_res(str[i] + j, &elem_f);
			else if (str[i][j] == 'C' && elem_f.res_x)
				get_color_res(str[i] + j, &elem_f);
		}
	}
	return (0);
}

void	free_tab(char **tab)
{
	while (*tab)
		free(*tab++);
}

int main()
{
		char **str;
		int i;
		
		i = -1;
		fill_tab(&str);
		while (str[++i])
			printf("%s\n", str[i]);
		if (parse_file(str) == -1)
			error_wall_map();
		 free_tab(str);
		return (0);
}