/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:41:26 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/18 10:59:50 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

void		*ft_memcpy(void *dst, const void *src, size_t size)
{
	char *dest;
	char *source;

	dest = (char *)dst;
	source = (char *)src;
	if (!source && !dest)
		return (NULL);
	while (size--)
		*dest++ = *source++;
	return (dst);
}

int			contain_newline(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strjoin(char const *s1, char const *s2, int *error)
{
	size_t	l_s1;
	size_t	l_s2;
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	if (!(str = malloc(sizeof(char) * (l_s1 + l_s2 + 1))))
	{
		*error = 1;
		return (NULL);
	}
	ft_memcpy(str, s1, l_s1);
	ft_memcpy(str + l_s1, s2, l_s2);
	str[l_s1 + l_s2] = 0;
	if (s1)
		free((void *)s1);
	return (str);
}

int			get_line_read(char *str, char **line, int *index)
{
	int		i;
	char	*new_str;

	i = 0;
	if (!str)
		return (0);
	while (str[*index] && str[*index] != '\n')
		(*index)++;
	if (!(new_str = malloc(sizeof(char) * (*index + 1))))
		return (1);
	while (str[i] && str[i] != '\n')
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = 0;
	*line = new_str;
	return (0);
}
