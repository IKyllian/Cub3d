/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by kdelport          #+#    #+#             */
/*   Updated: 2021/03/25 13:10:24 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	flood_fill(int y, int x, t_window *ptr)
{
	char	***map;

	map = &ptr->info_file.cpy_map;
	if ((*map)[y][x] == '1' || (*map)[y][x] == 'o' || (*map)[y][x] == 'x')
		return ;
	if ((*map)[y][x] == ' ')
		(*map)[y][x] = 'x';
	else
		(*map)[y][x] = 'o';
	if (y - 1 >= 0 && x < ft_strlen((*map)[y - 1]))
		flood_fill(y - 1, x, ptr);
	if (y - 1 >= 0 && x + 1 < ft_strlen((*map)[y - 1]))
		flood_fill(y - 1, x + 1, ptr);
	if (y - 1 >= 0 && x - 1 >= 0)
		flood_fill(y - 1, x - 1, ptr);
	if (y + 1 < ptr->info_file.map_size && x < ft_strlen((*map)[y + 1]))
		flood_fill(y + 1, x, ptr);
	if (y + 1 < ptr->info_file.map_size && x + 1 < ft_strlen((*map)[y + 1]))
		flood_fill(y + 1, x + 1, ptr);
	if (y + 1 < ptr->info_file.map_size && x - 1 >= 0)
		flood_fill(y + 1, x - 1, ptr);
	if (x + 1 < ft_strlen((*map)[y]))
		flood_fill(y, x + 1, ptr);
	if (x - 1 >= 0)
		flood_fill(y, x - 1, ptr);
}

void	print_str_debug(char **str)
{
	int	i = -1;
	while (str[++i])
		printf("%s\n", str[i]);
	printf("\n");
}

int	check_arg(char *str, char *arg, t_window *ptr)
{
	int	i;

	if (!str || !arg)
		ft_error("Probleme avec les arguments", 1, ptr);
	i = -1;
	while (str[++i] && arg[i])
		if (str[i] != arg[i])
			ft_error("Le second argument doit etre --save", 1, ptr);
	return (1);
}

int	main(int argc, char **argv)
{
	t_window	ptr;
	
	init_struct_ptr(&ptr);
	if (argc == 2 && check_arg(argv[1], "--save", &ptr))
		ptr.save = 1;
	ptr.info_file.file = malloc(sizeof(char *) * (get_file_size(&ptr) + 1));
	if (!ptr.info_file.file)
		ft_error("Erreur d'allocation.", 1, &ptr);
	fill_tab(&ptr);
	ptr.info_file.cpy_map = malloc(sizeof(char *) * \
		(ptr.info_file.map_size + 1));
	if (!ptr.info_file.cpy_map)
		ft_error("Erreur d'allocation.", 1, &ptr);
	fill_map_cpy(&ptr);
	// print_str_debug(ptr.info_file.file);
	// print_str_debug(ptr.info_file.map);
	// print_str_debug(ptr.info_file.cpy_map);
	flood_fill(ptr.info_file.start_y, ptr.info_file.start_x, &ptr);
	// print_str_debug(ptr.info_file.cpy_map);
	if (!map_is_valid(ptr.info_file.cpy_map, ptr.info_file.map_size, &ptr))
		ft_error("La map doit être fermée.", 1, &ptr);
	if (ptr.info_file.cpy_map)
		free_tab(ptr.info_file.cpy_map, ptr.info_file.cpy_map_allo_size);
	if (parse_file(&ptr) == -1)
		ft_error("Un parametre de config n'existe pas", 1, &ptr);
	//while (1) ;
	init_struct_fov(&ptr);
	ptr.player = init_struct_player(&ptr);
	create_window(&ptr);
	return (0);
}
