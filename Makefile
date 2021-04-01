NAME = cub3D
MLX_NAME =  libmlx.a
HEADER = cub3d.h

MLX_PATH = ./minilibx
MLX = -L minilibx -lmlx -framework OpenGL -framework AppKit

SRCS =  main.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		bitmap.c \
		colour_utils.c \
		display_minimap.c \
		event.c \
		fill_map_cpy.c \
		fov_utils.c \
		fov.c \
		ft_check_map.c \
		ft_errors.c \
		ft_frame.c \
		ft_get_info_utils.c \
		ft_get_map_info.c \
		ft_init_struct.c \
		ft_utils_file.c \
		ft_utils_file2.c \
		ft_wallcheck.c \
		manage_window.c \
		math_utils.c \
		mouvement_player.c \
		raycaster.c \
		sprite_calcs.c \
		sprite_init.c \
		sprite_utils.c \
		spriter.c \
		texture_init.c \

OBJS = $(SRCS:.c=.o)

CC = gcc
FLAGS = -g3 -O3 -Wextra -Werror -Wall
RM = rm -f

all : $(NAME)
 
%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME) : $(MLX_PATH)$(MLX_NAME) $(OBJS) $(HEADER)
	$(CC) $(FLAGS) -o $@ $(OBJS) $(MLX)

$(MLX_PATH)$(MLX_NAME) :
	@make -C $(MLX_PATH)

clean :
	$(RM) $(OBJS)
	@make clean -C $(MLX_PATH)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re all