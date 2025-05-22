CC = cc 
FLAGS = -Werror -Wall -Wextra
SRC_DIR = src
INCLUDE = -Iinclude
LIB_DIR = lib
MLX_A= $(LIB_DIR)/libmlx42.a
NAME = minirt
LIBFT = $(LIB_DIR)/libft.a
GNL = $(LIB_DIR)/libgnl.a
MLX_FLAG = -ldl -lglfw -pthread -lm 
SRC = $(SRC_DIR)/color.c  $(SRC_DIR)/get_normal.c $(SRC_DIR)/free.c $(SRC_DIR)/reserve.c $(SRC_DIR)/parse.c $(SRC_DIR)/main.c   $(SRC_DIR)/ray_cylinder.c  $(SRC_DIR)/ray_plane.c  $(SRC_DIR)/ray_sphere.c  $(SRC_DIR)/vector_math.c
OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDE) $(MLX_A) -o $(NAME)  $(MLX_FLAG) $(LIBFT) $(GNL) -g

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all