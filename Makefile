CC = cc 
FLAGS = -Werror -Wall -Wextra -g
SRC_DIR = src
INCLUDE = -Iinclude
LIB_DIR = lib
MLX_A= $(LIB_DIR)/libmlx42.a
NAME = minirt
LIBFT = $(LIB_DIR)/libft.a
GNL = $(LIB_DIR)/libgnl.a
MLX_FLAG = -ldl -lglfw -pthread -lm 
SRC =  src/calculate2.c src/color.c src/get_normal.c src/parse.c src/parse_utils2.c src/ray_cylinder.c src/ray_sphere.c src/reserve_obj.c src/test.c\
 src/calculate.c src/free.c src/main.c src/parse_objs.c src/parse_utils.c src/ray_plane.c src/reserve.c     'src/reserve utils.c'   src/vector_math.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDE) $(MLX_A) -o $(NAME)  $(MLX_FLAG) $(LIBFT) $(GNL)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all