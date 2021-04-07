/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/07 15:42:52 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	line_is_map(char *line)
{
	int	i;

	i = 0;
	if (*line >= 48 && *line <= 57)
		return (1);
	else if (*line == ' ' || *line == '\t')
	{
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '0' || line[i] == '1' || line[i] == '2'
			|| line[i] == '3' || line[i] == '4' || line[i] == '5'
			|| line[i] == '6')
			return (1);
	}
	return (0);
}

int	get_file_size(t_window *ptr, char *file)
{
	int		fd;
	int		ret;
	int		size;
	char	*line;

	size = 0;
	fd = open(file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (line)
			free(line);
		if (ret == -1)
			ft_error("Probleme lors de la lecture du fichier config", 1, ptr);
		size++;
	}
	close(fd);
	return (size);
}

void	fill_tab(t_window *ptr, char *file)
{
	int		fd;
	int		ret;
	int		i;
	char	*line;

	i = 0;
	fd = open(file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ret == -1)
			ft_error("Probleme lors de la lecture du fichier config.", 1, ptr);
		get_map_size(line, ptr, i);
		if (ptr->info_file.map_index > 0 && !line_is_map(line))
			ft_error("Le dernier element du fichier doit etre la map", 1, ptr);
		ptr->info_file.file_size++;
		ptr->info_file.file[i++] = line;
	}
	ptr->info_file.file[i] = NULL;
	if (ptr->info_file.map_index < 0)
		ft_error("Il doit y avoir une map dans le fichier", 1, ptr);
	ptr->info_file.map = ptr->info_file.file + ptr->info_file.map_index;
}

void	check_letters(t_window *ptr, char *str)
{
	if (str[0] == 'N' && ft_strlen(str) >= 3 && str[1] == 'O' && str[2] == ' ')
		get_info_texture(str, ptr);
	else if (str[0] == 'S' && ft_strlen(str) >= 3 && str[1] == 'O'
		&& str[2] == ' ')
		get_info_texture(str, ptr);
	else if (str[0] == 'W' && ft_strlen(str) >= 3 && str[1] == 'E'
		&& str[2] == ' ')
		get_info_texture(str, ptr);
	else if (str[0] == 'E' && ft_strlen(str) >= 3 && str[1] == 'A'
		&& str[2] == ' ')
		get_info_texture(str, ptr);
	else if (str[0] == 'R' && ft_strlen(str) >= 2 && str[1] == ' ')
		get_color_res(str, ptr);
	else if (str[0] == 'S' && ft_strlen(str) >= 2 && str[1] == ' ')
		get_color_res(str, ptr);
	else if (str[0] == 'F' && ft_strlen(str) >= 2 && str[1] == ' ')
		get_color_res(str, ptr);
	else if (str[0] == 'C' && ft_strlen(str) >= 2 && str[1] == ' ')
		get_color_res(str, ptr);
	else
		check_identifier_bonus(ptr, str);
}

int	parse_file(t_window *ptr)
{
	int		i;
	char	**file;

	i = -1;
	file = ptr->info_file.file;
	while (file[++i] && i < ptr->info_file.map_index)
		check_letters(ptr, file[i]);
	if (!file_is_valid(ptr))
		return (-1);
	return (0);
}
