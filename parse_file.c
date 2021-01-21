/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 10:53:10 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/20 16:47:17 by kdelport         ###   ########lyon.fr   */
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

void	fill_map_cpy(char ***cpy_map, char **str, int size , int index)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
		(*cpy_map)[i] = ft_strdup(str[index + i]);
	(*cpy_map)[i] = NULL;
	i = -1;
	while ((*cpy_map)[++i])
	{
		j = -1;
		while ((*cpy_map)[i][++j])
		{
			if ((*cpy_map)[i][j] != '1')
				(*cpy_map)[i][j] = '0';
		}
	}
}

int		fill_tab(char ***str, int *index)
{
	int		fd;
	int		ret;
	int		i;
	int 	size;
	char	*line;

	i = 0;
	size = 0;
	fd = open("text.cub", O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line_is_map(line))
		{
			if (*index < 0)
				*index = i;
			size++;
		}
		(*str)[i++] = line;
	}
	(*str)[i] = NULL;
	return (size);
}

void	flood_fill(int x, int y, char ***map, int size, char **str)
{
	if ((*map)[x][y] == '1' || (*map)[x][y] == 'o')
		return ;	
	(*map)[x][y] = 'o';
	if (x - 1 >= 0)
		flood_fill(x - 1, y, map, size, str); // North
	if (x - 1 >= 0 && y + 1 < ft_strlen((*map)[x]))
	  	flood_fill(x - 1, y + 1, map, size, str); //Diagonal North East
	if (x - 1 >= 0 && y - 1 >= 0)
	   	flood_fill(x - 1, y - 1, map, size, str); //Diagonal North West
	if (x + 1 < size)
		flood_fill(x + 1, y, map, size, str); //South
	if (x + 1 < size && y + 1 < ft_strlen((*map)[x]))
	  	flood_fill(x + 1, y + 1, map, size, str); //Diagonal South East
	if (x + 1 < size && y - 1 >= 0)
	  	flood_fill(x + 1, y - 1, map, size, str); //Diagonal South West
	if (y + 1 < ft_strlen((*map)[x]))
		flood_fill(x, y + 1, map, size, str); //East
	if (y - 1 >= 0)
		flood_fill(x, y - 1, map, size, str); //West
	return ;
}

int		map_is_valid(char **map, int size)
{
	int i;
	int j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		if (i == 0 || i == size - 1)
		{
			while (map[i][++j])
			{
				if ((map[i][j] != '1' && map[i][j] != '0'))
					return (0);
				if ((map[i][j] != '1' && map[i][j] != '0'))
					return (0);	
			}
		}
		else
		{
			if ((map[i][0] != '1' && map[i][0] != '0'))
				return (0);
			if ((map[i][ft_strlen(map[i]) - 1] != '1' && map[i][ft_strlen(map[i]) - 1] != '0'))
				return (0);	
		}
	}
	printf("Test\n");
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
	printf("Val N = %s\n", elem_f.t_no);
	printf("Val S = %s\n", elem_f.t_so);
	printf("Val E = %s\n", elem_f.t_ea);
	printf("Val W = %s\n", elem_f.t_we);
	printf("Val Sprite = %s\n", elem_f.sprite);
	printf("Val coord = %i - %i\n", elem_f.res_x, elem_f.res_y);
	printf("Val Ground = %i\n", elem_f.ground);
	printf("Val Ceiling = %i\n", elem_f.ceiling);
	return (0);
}

void	free_tab(char **tab)
{
	while (*tab)
		free(*tab++);
}

void	print_str_debug(char **str)
{
	int i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
	printf("\n");
}

int main()
{
	char **str;
	char **cpy_map;
	int i;
	int size;
	int index;
	
	i = 0;
	index = -1;
	size = fill_tab(&str, &index);
	if (!(cpy_map = malloc(sizeof(*cpy_map) * (size + 1))))
		return (0);
	fill_map_cpy(&cpy_map, str, size, index);
	i = -1;
	print_str_debug(str);
	print_str_debug(cpy_map);
	flood_fill(1, 3, &cpy_map, size, str + index);
	print_str_debug(cpy_map);
	if (!map_is_valid(cpy_map, size))
		error_wall_map(1);
	if (parse_file(str) == -1)
		error_wall_map();
	free_tab(str);
	return (0);
}