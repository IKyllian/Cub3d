/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 12:54:33 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/06 12:26:54 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static	void	data_to_bitmap(t_window *ptr, int fd)
{
	int	i;
	int	j;
	int	*img;

	img = (int *)ptr->image.addr;
	i = ptr->info_file.res_y - 1;
	while (i >= 0)
	{
		j = -1;
		while (++j < ptr->info_file.res_x)
			write(fd, &img[i * ptr->info_file.res_x + j], 4);
		i--;
	}
}

static	void	bitmap_info_header(t_window *ptr, int fd)
{
	int	header_info_size;
	int	plane_nbr;
	int	count;

	header_info_size = 40;
	plane_nbr = 1;
	count = -1;
	write(fd, &header_info_size, 4);
	write(fd, &ptr->info_file.res_x, 4);
	write(fd, &ptr->info_file.res_y, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &ptr->info_file.bit_pxl, 2);
	while (++count < 28)
		write(fd, "\0", 1);
}

int	create_bitmap(t_window *ptr)
{
	int	fd;
	int	file_size;
	int	first_pix;

	fd = open("image.bmp", O_CREAT | O_RDWR, 00744);
	file_size = 14 + 40 + 4 + \
		(ptr->info_file.res_x * ptr->info_file.res_y * 4);
	first_pix = 14 + 40 + 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bitmap_info_header(ptr, fd);
	data_to_bitmap(ptr, fd);
	close(fd);
	return (1);
}
