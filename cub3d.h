/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:56:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/26 14:14:17 by kdelport         ###   ########lyon.fr   */
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

typedef struct s_info_file
{
	int 	res_x;
	int 	res_y;
	char 	*t_no;
	char 	*t_so;
	char 	*t_we;
	char 	*t_ea;
	char 	*sprite;
	int 	ground;
	int 	ceiling;
	char	**file;
	int		map_size;
	int		map_index;
	char	**cpy_map;
	int		start_x;
	int		start_y;
}				t_info_file;

typedef struct s_player
{
	float pos_x;
	float pos_y; 

}				t_player;

typedef struct s_window
{
	void	*mlx;
	void 	*win;
	int		is_press;

}				t_window;

int			get_next_line(int fd, char **line);
char		*get_next_save(char *str, int *error, int *index);
int			final_check(char **final_str, char **line, char *buffer, int ret);
int			ft_strlen(const char *s);
void		*ft_memcpy(void *dst, const void *src, int size);
int			contain_newline(char *str);
char		*ft_strjoin(char const *s1, char const *s2, int *error);
int			get_line_read(char *str, char **line, int *index);
void		*ft_calloc(size_t element_count, size_t element_size);
void		*ft_memset(void *s, int c, size_t n);

void		get_info_texture(char *str, t_info_file *elem_f);
char 		*get_info_str(char *str);
void		get_info_coord(char *str, t_info_file *elem_f);
int			get_info_color(char *str);
void		get_color_res(char *str, t_info_file *elem_f);
void		error_wall_map();
int			create_trgb(int t, int r, int g, int b);
void		fill_tab(t_info_file *elem_f);
int			line_is_map(char *line);
char		*ft_strdup(const char *source);

int			get_file_size(void);
void		init_struct_file(t_info_file *elem_f);
void		init_struct_ptr(t_window *ptr);
void		init_struct_player(t_player *player);
int			parse_file(t_info_file *elem_f);
int			map_is_valid(char **map, int size);
void		check_start_pos(t_info_file *elem_f, int *start_pos, int i, int j);
void		fill_map_tab(t_info_file *elem_f, int i, int max_size, int *start_pos);
void		fill_map_cpy(t_info_file *elem_f);
int			key_pressed(int keycode, t_window *ptr);

#endif