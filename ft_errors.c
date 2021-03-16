/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/16 11:44:31 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(int error)
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
		printf("Error\nLe fichier de texture n'existe pas");
	exit(1);
}
