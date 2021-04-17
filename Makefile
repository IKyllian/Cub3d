NAME = cub3D
MLX_NAME =  libmlx.a
HEADER = cub3d.h

MLX_PATH = ./minilibx
MLX = -L minilibx -lmlx -framework OpenGL -framework AppKit

RES = 0

SRCS =  main.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		bitmap.c \
		colour_utils.c \
		display_minimap.c \
		event.c \
		fill_map_cpy.c \
		fov_utils.c \
		fov.c \
		errors.c \
		frame.c \
		freedom.c \
		init_utils.c \
		get_map_info.c \
		init_struct.c \
		select_side.c \
		utils_file.c \
		parse_utils.c \
		parse_file_utils.c \
		wallcheck.c \
		init_image.c \
		manage_window.c \
		math_utils.c \
		mouvement_player.c \
		mouvement_player2.c \
		raycaster.c \
		skybox.c \
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