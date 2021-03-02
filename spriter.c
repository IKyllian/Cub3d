#include "cub3d.h"

void	put_sprite(t_texture texture, t_window *ptr)
{
	int	tex_x;
	int	tex_y;

	tex_x = fmodf(ptr->ray.nwall_x, 1) * texture.width;
	if (fmodf(ptr->ray.nwall_x, 1) == 0)
		tex_x = fmodf(ptr->ray.nwall_y, 1) * texture.width;
	tex_y = (ptr->ray.pos - ptr->ray.u_wall) * texture.height
		/ (ptr->ray.l_wall - ptr->ray.u_wall);
	if (tex_y > texture.height - 1)
		tex_y -= 1;
	// my_mlx_pixel_put(ptr, ptr->ray.id, ptr->ray.pos,
	// 	texture.addr[tex_y * texture.width + tex_x]);
}

void	sprite_check(t_window *ptr)
{
	put_sprite(ptr->sp_tex, ptr);
}
