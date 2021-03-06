/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by kdelport          #+#    #+#             */
/*   Updated: 2021/04/17 12:17:17 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	flood_fill(int y, int x, t_window *ptr)
{
	char	***map;

	map = &ptr->info_file.cpy_map;
	if (x < 0 || y < 0 || x >= ptr->info_file.map_width
		|| y >= ptr->info_file.map_size)
		return ;
	if ((*map)[y][x] == '1' || (*map)[y][x] == 'o')
		return ;
	if ((*map)[y][x] == ' ')
		ft_error("La map n'est pas fermé", 1, ptr, 0);
	if (x <= 0 || x >= ptr->info_file.map_width - 1
		|| y <= 0 || y >= ptr->info_file.map_size - 1)
		ft_error("La map n'est pas fermé", 1, ptr, 0);
	(*map)[y][x] = 'o';
	flood_fill(y - 1, x, ptr);
	flood_fill(y - 1, x + 1, ptr);
	flood_fill(y - 1, x - 1, ptr);
	flood_fill(y + 1, x, ptr);
	flood_fill(y + 1, x + 1, ptr);
	flood_fill(y + 1, x - 1, ptr);
	flood_fill(y, x + 1, ptr);
	flood_fill(y, x - 1, ptr);
}

int	check_arg(char *str, char *arg)
{
	int	i;

	if (!str || !arg)
		ft_arg_error("Probleme avec les arguments");
	i = -1;
	while (arg[++i])
		if (str[i] != arg[i])
			ft_arg_error("Le second argument doit etre --save");
	return (1);
}

int	check_extension(char *str, char *arg)
{
	int	i;
	int	j;

	i = ft_strlen(str);
	j = ft_strlen(arg);
	while (--j >= 0 && --i >= 0)
		if (arg[j] != str[i])
			ft_arg_error("L'extension du fichier config doit etre .cub");
	return (1);
}

void	start_game(int save, char *file)
{
	t_window	ptr;

	init_struct_ptr(&ptr);
	if (save)
		ptr.save = 1;
	get_file_size(&ptr, file);
	ptr.info_file.file = malloc(sizeof(char *) * (ptr.info_file.map_index + 1));
	if (!ptr.info_file.file)
		ft_error("Erreur d'allocation.", 1, &ptr, 0);
	ptr.info_file.map = malloc(sizeof(char *) * (ptr.info_file.map_size + 1));
	if (!ptr.info_file.map)
		ft_error("Erreur d'allocation.", 1, &ptr, 0);
	fill_tab(&ptr, file);
	ptr.info_file.cpy_map = malloc(sizeof(char *) * \
		(ptr.info_file.map_size + 1));
	if (!ptr.info_file.cpy_map)
		ft_error("Erreur d'allocation.", 1, &ptr, 0);
	fill_map_cpy(&ptr);
	flood_fill(ptr.info_file.start_y, ptr.info_file.start_x, &ptr);
	if (parse_file(&ptr) == -1)
		ft_error("Un parametre de config n'existe pas", 1, &ptr, 0);
	fill_struct_fov(&ptr);
	ptr.player = init_struct_player(&ptr);
	create_window(&ptr);
}

int	main(int argc, char **argv)
{
	int	save;

	save = 0;
	if (argc < 2)
		ft_arg_error("Il manque un fichier de config en premier parametre");
	else if (argc > 3)
		ft_arg_error("Trop d'arguments");
	else if (argc >= 2 && check_extension(argv[1], ".cub"))
	{
		if (argc == 3 && check_arg(argv[2], "--save"))
			save = 1;
		start_game(save, argv[1]);
	}
	return (0);
}
