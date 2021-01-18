/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/18 15:53:03 by kdelport         ###   ########lyon.fr   */
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

void	init_struct(t_elem_file *info_file)
{
	info_file->res = 0;
	info_file->t_no = 0;
	info_file->t_so = 0;
	info_file->t_we = 0;
	info_file->t_ea = 0;
	info_file->sprite = 0;
	info_file->ground = 0;
	info_file->ceiling = 0;
}

int		parse_file(char **str)
{
	int i;
	int j;
	t_elem_file info_file;

	i = -1;
	init_struct(&info_file);
	while (str[++i])
	{
		j = -1;
		while (str[i][++j])
		{
			while (str[i][j] == ' ')
				j++;
			if (str[i][j] == 'N' && str[i][j] == 'O' && !info_file.t_no)
				get_info_texture('N', &j, &info_file);
			else if (str[i][j] == 'S' && str[i][j] == 'O' && !info_file.t_so)
				get_info_texture('S', &j, &info_file);
			else if (str[i][j] == 'W' && str[i][j] == 'E' && !info_file.t_we)
				get_info_texture('E', &j, &info_file);
			else if (str[i][j] == 'E' && str[i][j] == 'A' && !info_file.t_ea)
				get_info_texture('W', &j, &info_file);
			else if (str[i][j] == 'R')
				...
			else if (str[i][j] == 'S')
				...
			else if (str[i][j] == 'F')
				...
			else if (str[i][j] == 'C')
				...
		}
	}
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
		if (parse_tab(str) == -1)
			error_wall_map();
		 free_tab(str);
		return (0);
}