/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:47:14 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/10 15:28:25 by kdelport         ###   ########lyon.fr   */
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
	int		ret;
	int		size;
	char	*line;

	size = 0;
	ptr->info_file.fd = open(file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(ptr->info_file.fd, &line);
		get_map_size(line, ptr, size);
		if (ptr->info_file.map_index > 0 && !line_is_map(line))
			ft_error("Le dernier element du fichier doit etre la map", \
				1, ptr, 1);
		if (line)
			free(line);
		if (ret == -1)
			ft_error("Probleme lors de la lecture du fichier config", \
				1, ptr, 1);
		size++;
	}
	close(ptr->info_file.fd);
	if (ptr->info_file.map_index < 0)
		ft_error("Il doit y avoir une map dans le fichier", 1, ptr, 0);
	return (size);
}

void	fill_tab(t_window *ptr, char *file)
{
	int		ret;
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	ptr->info_file.fd = open(file, O_RDONLY);
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(ptr->info_file.fd, &line);
		if (ret == -1)
			ft_error("Probleme lors de la lecture du fichier config.", \
				1, ptr, 1);
		if (!line_is_map(line))
			ptr->info_file.file[i++] = line;
		else
			ptr->info_file.map[j++] = line;
		ptr->info_file.file_size++;
	}
	ptr->info_file.file[i] = NULL;
	ptr->info_file.map[j] = NULL;
	close(ptr->info_file.fd);
}

void	check_letters(t_window *ptr, char *str)
{
	if (str[0] == 'N' && ft_strlen(str) >= 3 && str[1] == 'O' )
		get_info_texture(str, ptr);
	else if (str[0] == 'S' && ft_strlen(str) >= 3 && str[1] == 'O')
		get_info_texture(str, ptr);
	else if (str[0] == 'W' && ft_strlen(str) >= 3 && str[1] == 'E')
		get_info_texture(str, ptr);
	else if (str[0] == 'E' && ft_strlen(str) >= 3 && str[1] == 'A')
		get_info_texture(str, ptr);
	else if (str[0] == 'R' )
		get_info_sprite(str, ptr);
	else if (str[0] == 'F' )
		get_info_sprite(str, ptr);
	else if (str[0] == 'C' )
		get_info_sprite(str, ptr);
	else
		check_identifier_bonus(ptr, str);
}

int	parse_file(t_window *ptr)
{
	int		i;
	char	**file;

	i = -1;
	file = ptr->info_file.file;
	while (file[++i])
		check_letters(ptr, file[i]);
	if (!file_is_valid(ptr))
		return (-1);
	ptr->ratio = (int)((ptr->info_file.res_x / ptr->info_file.res_y \
		+ ptr->info_file.res_x / 5 + ptr->info_file.res_y / 5) \
		/ (ptr->info_file.map_width / ptr->info_file.map_size \
		+ ptr->info_file.map_width + ptr->info_file.map_size));
	if (ptr->ratio <= 0)
		ptr->ratio = 1;
	return (0);
}
