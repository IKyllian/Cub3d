#include "cub3d.h"

t_image	img_init(t_window *ptr)
{
	t_image		image;

	image.ptr = mlx_new_image(ptr->mlx, ptr->info_file.res_x, ptr->info_file.res_y);
	image.addr = mlx_get_data_addr(image.ptr, &image.bpp, &image.len, &image.endian);
	return (image);
}

void	my_mlx_pixel_put(t_window *ptr, int x, int y, int color)
{
	char	*dst;

	dst = ptr->img.addr + (y * ptr->img.len + x * (ptr->img.bpp / 8));
	*(unsigned int *)dst = color;
}

int	frame_gen(t_window *ptr)
{
	//mlx_clear_window(ptr->ptr, ptr->win);
	print_minimap(ptr);
	put_camera(ptr);
	put_player(ptr);
	put_fov(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.ptr, 0, 0);
	return (0);
}