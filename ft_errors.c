/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/15 14:44:52 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, int is_error, t_window *ptr, int close_file)
{
	if (is_error == 2)
		printf("%s\n", str);
	else if (is_error)
		printf("Error\n%s\n", str);
	if (close_file)
		close(ptr->info_file.fd);
	ft_freedom(ptr);
	exit(0);
}

void	ft_arg_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}
