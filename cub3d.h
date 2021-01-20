/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdelport <kdelport@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 10:56:57 by kdelport          #+#    #+#             */
/*   Updated: 2021/01/20 14:42:52 by kdelport         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

typedef struct s_info_file
{
	int res_x;
	int res_y;
	char *t_no;
	char *t_so;
	char *t_we;
	char *t_ea;
	char *sprite;
	int ground;
	int ceiling;
}				t_info_file;

typedef struct s_info_map
{

}				t_info_map;

int			get_next_line(int fd, char **line);
char		*get_next_save(char *str, int *error, int *index);
int			final_check(char **final_str, char **line, char *buffer, int ret);
size_t		ft_strlen(const char *s);
void		*ft_memcpy(void *dst, const void *src, size_t size);
int			contain_newline(char *str);
char		*ft_strjoin(char const *s1, char const *s2, int *error);
int			get_line_read(char *str, char **line, int *index);

void		get_info_texture(char *str, t_info_file *elem_f);
char 		*get_info_str(char *str, t_info_file *elem_f);
void		get_info_coord(char *str, t_info_file *elem_f);
int			get_info_color(char *str, t_info_file *elem_f);
void		get_color_res(char *str, t_info_file *elem_f);
void		error_wall_map();
int			create_trgb(int t, int r, int g, int b);
int			fill_tab(char ***str, int *index);
int			line_is_map(char *line);
char		*ft_strdup(const char *source);

#endif