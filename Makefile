NAME = fractol
FLAGS = -Wall -Werror -Wextra
SRCS = srcs/*.c
OBJS = *.o
INCLUDES = includes

all: $(NAME)

$(OBJS):
	@gcc -c $(SRCS) -I$(INCLUDES) -I./minilibx_macos

$(NAME): $(OBJS)
	make -C minilibx_macos
	@gcc $(OBJS) -o $(NAME) -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit -framework OpenCL

clean:
	@rm -f $(OBJS)
	make -C minilibx_macos clean

fclean: clean
	@rm -f $(NAME)

re: fclean all
