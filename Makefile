NAME = fractol
FLAGS = -Wall -Werror -Wextra
SRCS = srcs/*.c
OBJS = *.o
INCLUDES = includes

all: $(NAME)

$(OBJS):
	@gcc -c $(SRCS) -I$(INCLUDES)

$(NAME): $(OBJS)
	@gcc $(OBJS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit -framework OpenCL

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all