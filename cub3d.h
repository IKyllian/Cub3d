/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:56:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/03/26 12:43:10 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "./minilibx/mlx.h"

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40

typedef struct 	s_info_file
{
	int 		res_x;
	int 		res_y;
	char 		*t_no;
	char 		*t_so;
	char 		*t_we;
	char 		*t_ea;
	char 		*t_sprite;
	int 		ground;
	int 		ceiling;
	char		**file;
	char		**map;
	int			map_width;
	int			map_size;
	int			file_size;
	int			map_index;
	char		**cpy_map;
	int			cpy_map_allo_size;
	int			start_x;
	int			start_y;
	int			nb_sprite;
	int			sprite_allo_size;
	int			bit_pxl;
}				t_info_file;

typedef struct	s_input
{
	int			forward;
	int			backward;
	int			strafe_l;
	int			strafe_r;
	int			rotate_l;
	int			rotate_r;
	int			crouch;
}				t_input;

typedef struct 	s_player
{
	float 		pos_x;
	float 		pos_y;
	float		f_x;
	float		f_y;
}				t_player;

typedef struct	s_image {
	void		*ptr;
	char		*addr;
	int			bpp;
	int			len;
	int			endian;
}				t_image;

typedef struct s_ray
{
	int			id;
	int			pos;
	int			side;
	float		nwall_x;
	float		nwall_y;
	int			shift_x;
	int			shift_y;
	float		dist_x;
	float		dist_y;
	float		s_x;
	float		s_y;
	float		n_x;
	float		n_y;
	int			u_wall;
	int			l_wall;
}				t_ray;

typedef struct s_fov
{
	int			fov;
	float		vect_x;
	float		vect_y;
	float		*dist;
}				t_fov;

typedef struct	s_sprites {
	int			id;
	int			type;
	int			visible;
	int			active;
	float		x;
	float		y;
	float		dist;
	float		r_x;
	float		r_y;
	float		d_x;
	float		d_y;
	float		size_x;
	float		size_y;
	int			u_coord;
	int			b_coord;
	int			l_coord;
	int			r_coord;
}				t_sprites;

typedef struct s_texture
{
	void	*ptr;
	int		*addr;
	int		width;
	int		height;
	int		bits_pxl;
	int		len_line;
	int		endian;
}				t_texture;

typedef struct 	s_window
{
	void		*mlx;
	void 		*win;
	int			is_press;
	int			ratio;
	int			save;
	t_info_file info_file;
	t_player 	player;
	t_input		input;
	t_image		image;
	t_ray		ray;
	t_fov		fov;
	t_texture	n_tex;
	t_texture	s_tex;
	t_texture	e_tex;
	t_texture	o_tex;
	t_texture	sp_tex;
	t_sprites	**sprite;
}				t_window;

int			get_next_line(int fd, char **line);
char		*get_next_save(char *str, int *error, int *index);
int			final_check(char **final_str, char **line, char *buffer, int ret);
int			ft_strlen(const char *s);
void		*ft_memcpy(void *dst, const void *src, int size);
int			contain_newline(char *str);
char		*ft_strjoin(char const *s1, char const *s2, int *error);
int			get_line_read(char *str, char **line, int *index);
void		free_tab(char **tab, int len);

void		get_info_texture(char *str,  t_window *ptr);
char 		*get_info_str(char *str, t_window *ptr, int is_sprite);
void		get_info_coord(char *str,  t_window *ptr);
int			get_info_color(char *str, t_window *ptr);
void		get_color_res(char *str,  t_window *ptr);
void		get_number(char **str, t_window *ptr, int *color, int is_color);
void		ft_error(char *str, int is_error, t_window *ptr);
int			ft_trgb(int t, int r, int g, int b);
void		fill_tab(t_window *ptr);
void		get_map_size(char *line, t_window *ptr, int i);
int			line_is_map(char *line);
int			file_is_valid(t_window *ptr);
void		line_is_false(char *line, int ret, t_window *ptr);
int			info_exist(char *str, int nbr, t_window *ptr);

int			get_file_size(t_window *ptr);
void		init_struct_file(t_info_file *elem_f);
void		init_struct_ptr(t_window *ptr);
t_player	init_struct_player(t_window *ptr);
void		init_struct_fov(t_window *ptr);
void		init_struct_ray(t_window *ptr);
void		input_init(t_window *ptr);
int			parse_file(t_window *ptr);
int			map_is_valid(char **map, int size, t_window *ptr);
int			map_character_is_valid(char *line, t_window *ptr);
void		check_start_pos(t_window *ptr, int *start_pos, int i, int j);
void		fill_map_tab(t_window *ptr, int i, int max_size, int *start_pos);
void		fill_map_cpy(t_window *ptr);
int			key_quit(int keycode, t_window *ptr);
void		create_window(t_window *ptr);

int			key_move(t_window *ptr);
int			pl_rotation(int keycode, t_window *ptr, float speed);
int			pl_move(int keycode, t_window *ptr, float speed);

int 		is_collision(char dir, t_window *ptr, float speed);
void		display_map(t_window *ptr);
void		display_player(t_window *ptr);

void		wall_dist_calc(char dir, t_window *ptr);
int			wall_check(float x, float y, t_window *ptr);
void		inverse_cam(char dir, t_window *ptr);
void		img_init(t_window *ptr);

void		put_fov(t_window *ptr);
int			frame_gen(t_window *ptr);
void		my_mlx_pixel_put(t_window *ptr, int x, int y, int color);
void		ray_cannon(float fish, t_window *ptr);

void		create_text_struct(t_window *ptr);
void		sprite_init(t_window *ptr);
void		fill_text_struct(t_window *ptr, t_texture *texture, char *tex);
t_texture	init_text_struct();
void		sprite_check(t_window *ptr);

int			anglizer(float vx1, float vy1, float vx2, float vy2);
float		deg_rad(float deg);
float		rad_deg(float rad);
float		ft_dist(float x1, float y1, float x2, float y2);
float		dist_calc(float x, float y);

void		sprite_dist(t_window *ptr);
void		sprite_sizer(int i, t_window *ptr);
void		sprite_reset(t_window *ptr);
void		sprite_xpos(int i, t_window *ptr);
void		sprite_sort(t_window *ptr);
//void		sprite_enable(int i, t_window *ptr);

int			create_bitmap(t_window *ptr);
int			step_init(float cam, float start, float pl);

int			key_press(int keycode, t_window *ptr);
int			key_release(int keycode, t_window *ptr);
void		find_x(t_window *ptr);
void		find_y(t_window *ptr);
int			is_valid_coord(float x, float y, int shft_x, int shft_y, t_window *ptr);

#endif