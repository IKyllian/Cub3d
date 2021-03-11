#include "cub3d.h"

void	sprite_dist(t_window *ptr)
{
	int		i;
	float	x;
	float	y;

	i = 0;
	while (i < ptr->info_file.nb_sprite)
	{
		x = ptr->sprite[i]->x;
		y = ptr->sprite[i]->y;
		ptr->sprite[i]->dist = sqrtf(powf(x - ptr->player.pos_x, 2)
				+ powf(y - ptr->player.pos_y, 2));
		i++;
	}
}

void	sprite_sizer(int i, t_window *ptr)
{
	int	ray_height;
	int	size;
	
	// ptr->sprite[i]->size_x = ptr->sprite_txt->width * ptr->sprite[i]->dist;
	// ptr->sprite[i]->size_y = ptr->sprite_txt->height * ptr->sprite[i]->dist;
	ray_height = (int)(ptr->info_file.res_y / ptr->sprite[i]->dist);
	ptr->sprite[i]->u_coord = - ((float)ray_height) / 2 + (float)ptr->info_file.res_y / 2;
	ptr->sprite[i]->b_coord = (float)ray_height / 2 + (float)ptr->info_file.res_y / 2;
	size = ptr->sprite[i]->b_coord - ptr->sprite[i]->u_coord;
	// ptr->sprite[i]->size_x = ptr->sprite_txt->width * ((d_wall - ptr->sprite[i]->dist) / d_wall);
	// ptr->sprite[i]->size_y = ptr->sprite_txt->height * ((d_wall - ptr->sprite[i]->dist) / d_wall);
	// if (ptr->sprite[i]->id == 0)
	// 	printf("%iy\t%i\n", i, abs(ptr->sprite[i]->u_coord - ptr->sprite[i]->b_coord));
	
	ptr->sprite[i]->l_coord = (float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x - size / 2;
	ptr->sprite[i]->r_coord = (float)ptr->info_file.res_x / 2 + ptr->sprite[i]->r_x + size / 2;
	// if (ptr->sprite[i]->id == 0)
	// 	printf("x\t%i\n", abs(ptr->sprite[i]->l_coord - ptr->sprite[i]->r_coord));
}