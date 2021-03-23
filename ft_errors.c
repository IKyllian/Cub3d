/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/23 15:10:32 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab, int len)
{
	while (--len >= 0)
		free(tab[len]);
	free(tab);
}

void	ft_freedom(t_window *ptr)
{
	int	i;

	i = ptr->info_file.sprite_allo_size;
	//Elems a free : File, cpy map (free dans le main), tableau de sprites, tous les path dans le fichier .cub
	//Probleme free line avec gnl
	if (ptr->sprite)
	{
		printf("Sprite\n");
		while (--i)
			free(ptr->sprite[i]);
		free(ptr->sprite);
	}
	if (ptr->info_file.file)
	{
		printf("File\n");
		free_tab(ptr->info_file.file, ptr->info_file.file_size);
	}
	if (ptr->info_file.t_no)
	{
		printf("NO\n");
		free(ptr->info_file.t_no);
	}
	if (ptr->info_file.t_so)
	{
		printf("SO\n");
		free(ptr->info_file.t_so);
	}
	if (ptr->info_file.t_ea)
	{
		printf("EA\n");
		free(ptr->info_file.t_ea);
	}
	if (ptr->info_file.t_we)
	{
		printf("WE\n");
		free(ptr->info_file.t_we);
	}
	if (ptr->info_file.t_sprite)
	{
		printf("T_Sprite\n");
		free(ptr->info_file.t_sprite);
	}
}

void	ft_error(int error, t_window *ptr)
{
	if (error == 1)
		printf("Error\nLa map doit être fermée.\n");
	else if (error == 2)
		printf("Error\nIl ne peut y avoir que une position de depart.\n");
	else if (error == 3)
		printf("Error\nIl doit y avoir au moins une position de depart.\n");
	else if (error == 4)
		printf("Error\nErreur d'allocation.\n");
	else if (error == 5)
		printf("Error\nLe fichier config n'est pas complet");
	else if (error == 6)
		printf("Error\nUn parametre de config est en double");
	else if (error == 7)
		printf("Error\nErreur de map");
	else if (error == 8)
		printf("Error\nUne ligne est incorrect dans le fichier");
	else if (error == 9)
		printf("Error\nLa valeur d'une des couleurs est superieur a 255");
	else if (error == 10)
		printf("Error\nProbleme avec le second argument");
	else if (error == 11)
		printf("Error\nUn fichier de texture n'existe pas");
	else if (error == 12)
		printf("Error\nUn caractere est incorrecte dans la map");
	ft_freedom(ptr);
	//while (1);
	exit(1);
}
