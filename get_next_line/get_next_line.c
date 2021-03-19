/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:06:22 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/17 15:32:08 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*get_next_save(char *str, int *error, int *index)
{
	size_t	len_str;
	size_t	i;
	char	*new_str;

	i = 0;
	len_str = (size_t)*index;
	if (!str[len_str++])
	{
		free(str);
		return (NULL);
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len_str + 1));
	if (!new_str)
	{
		*error = 1;
		return (NULL);
	}
	while (str[len_str + i])
	{
		new_str[i] = str[len_str + i];
		i++;
	}
	new_str[i] = 0;
	free(str);
	return (new_str);
}

int	free_elems(char *buffer, char *final_str)
{
	if (final_str)
		free(final_str);
	free(buffer);
	return (-1);
}

int	final_check(char **final_str, char **line, char *buffer, int ret)
{
	int	error;
	int	index;

	error = 0;
	index = 0;
	if (get_line_read(*final_str, line, &index) == 1)
		return (free_elems(buffer, *final_str));
	*final_str = get_next_save(*final_str, &error, &index);
	if (error)
		return (free_elems(buffer, *final_str));
	free(buffer);
	if (!ret)
		return (0);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	int			ret;
	char		*buffer;
	static char	*final_str;
	int			error;

	buffer = malloc(sizeof(char) * (1 + 1));
	if (!line || fd < 0 || !buffer)
		return (-1);
	ret = 1;
	error = 0;
	while (ret && (!contain_newline(final_str)))
	{
		ret = read(fd, buffer, 1);
		if (error || ret == -1)
			return (free_elems(buffer, final_str));
		buffer[ret] = 0;
		final_str = ft_strjoin(final_str, buffer, &error);
	}
	return (final_check(&final_str, line, buffer, ret));
}
