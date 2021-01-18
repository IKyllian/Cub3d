NAME = cub3d
HEADER = cub3d.h
# cub3d.c
SRCS = parse_map.c get_next_line.c get_next_line_utils.c ft_errors.c
OBJS = $(SRCS:.c=.o)

CC = gcc
FLAGS = -Wextra -Werror -Wall
RM = rm -f

all : $(NAME)

%.o : %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME) : $(OBJS) $(HEADER)
	ar cr $(NAME) $(OBJS)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : clean fclean re all