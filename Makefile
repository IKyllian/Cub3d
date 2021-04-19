NAME = cub3D
MLX_NAME =  libmlx.a
HEADER = ./includes/cub3d.h

MLX_PATH = ./minilibx
MLX = -L minilibx -lmlx -framework OpenGL -framework AppKit

RES = 0

SRCS =  main.c \
		./get_next_line/get_next_line.c ./get_next_line/get_next_line_utils.c \
		bitmap.c \
		./engine/colour_utils.c \
		./engine/display_minimap.c \
		./engine/movements/event.c \
		./parsing/fill_map_cpy.c \
		./engine/fov_utils.c \
		./engine/fov.c \
		./error-free/errors.c \
		./engine/frame.c \
		./error-free/freedom.c \
		./init/init_utils.c \
		./parsing/get_map_info.c \
		./init/init_struct.c \
		./init/select_side.c \
		./parsing/utils_file.c \
		./parsing/parse_utils.c \
		./parsing/parse_file_utils.c \
		./engine/wallcheck.c \
		./init/init_image.c \
		./engine/manage_window.c \
		./engine/math_utils.c \
		./engine/movements/mouvement_player.c \
		./engine/movements/mouvement_player2.c \
		./engine/raycaster.c \
		./engine/skybox.c \
		./engine/sprites/sprite_calcs.c \
		./engine/sprites/sprite_init.c \
		./engine/sprites/sprite_utils.c \
		./engine/sprites/spriter.c \
		./init/texture_init.c \

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

bonus : $(MLX_PATH)$(MLX_NAME) $(OBJS) $(HEADER)
		$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(MLX)
clean :
		$(RM) $(OBJS)
		@make clean -C $(MLX_PATH)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re all