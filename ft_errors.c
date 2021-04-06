/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 13:17:37 by kdelport          #+#    #+#             */
/*   Updated: 2021/04/06 11:40:02 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(char **tab, int len)
{
	while (--len >= 0)
		free(tab[len]);
	free(tab);
}

void	free_tex(t_window *ptr , t_texture *tex, char **path)
{
	if (tex->ptr)
		mlx_destroy_image(ptr->mlx, tex->ptr);
	free(*path);
}

void	ft_freedom(t_window *ptr)
{
	int	i;

	i = ptr->info_file.sprite_allo_size;
	//Elems a free : File, cpy map (free dans le main), tableau de sprites, tous les path dans le fichier .cub + la texture qui va avec, shade (ptr->fov), skybox
	//Probleme free line avec gnl
	if (ptr->sprite)
	{
		printf("\nSprite\n");
		while (--i)
			free(ptr->sprite[i]);
		free(ptr->sprite);
	}
	if (ptr->image.ptr)
	{
		printf("Image ptr\n");
		mlx_destroy_image(ptr->mlx, ptr->image.ptr);
	}
	if (ptr->fov.dist)
	{
		printf("Dist\n");
		free(ptr->fov.dist);
	}
	if (ptr->fov.shade)
	{
		printf("Shade\n");
		free(ptr->fov.shade);
	}
	if (ptr->info_file.file)
	{
		printf("\nFile\n");
		free_tab(ptr->info_file.file, ptr->info_file.file_size);
	}
	if (ptr->info_file.t_no)
	{
		printf("\nNO\n");
		free_tex(ptr, &ptr->n_tex, &ptr->info_file.t_no);
	}
	if (ptr->info_file.t_so)
	{
		printf("\nSO\n");
		free_tex(ptr, &ptr->s_tex, &ptr->info_file.t_so);
	}
	if (ptr->info_file.t_ea)
	{
		printf("\nEA\n");
		free_tex(ptr, &ptr->e_tex, &ptr->info_file.t_ea);
	}
	if (ptr->info_file.t_we)
	{
		printf("\nWE\n");
		free_tex(ptr, &ptr->o_tex, &ptr->info_file.t_we);
	}
	if (ptr->info_file.t_sprite)
	{
		printf("\nT_Sprite\n");
		free_tex(ptr, &ptr->sp_tex, &ptr->info_file.t_sprite);
	}
	if (ptr->info_file.t_second_sprite)
	{
		printf("\nSeconde T_Sprite\n");
		free_tex(ptr, &ptr->second_sp_tex, &ptr->info_file.t_second_sprite);
	}
	if (ptr->info_file.t_trap_sprite)
	{
		printf("\nTrap T_Sprite\n");
		free_tex(ptr, &ptr->trap_sp_tex, &ptr->info_file.t_trap_sprite);
	}
	if (ptr->info_file.t_heal_sprite)
	{
		printf("\nHeal T_Sprite\n");
		free_tex(ptr, &ptr->heal_sp_tex, &ptr->info_file.t_heal_sprite);
	}
	if (ptr->info_file.skybox)
	{
		printf("\nSkybox\n");
		free_tex(ptr, &ptr->skybox, &ptr->info_file.skybox);
	}
	if (ptr->mlx && ptr->win)
	{
		printf("Window ptr\n");
		mlx_destroy_window(ptr->mlx, ptr->win);
	}
}

void	ft_error(char *str, int is_error, t_window *ptr)
{
	if (is_error)
		printf("Error\n%s\n", str);
	ft_freedom(ptr);
	//while (1);
	exit(1);
}

void	ft_arg_error(char *str)
{
	printf("Error\n%s\n", str);
	exit(1);
}