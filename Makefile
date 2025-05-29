CC = cc
FLAGS = -Werror -Wall -Wextra -g
SRC_DIR = src
INCLUDE = -Iinclude
LIB_DIR = lib
MLX_A = $(LIB_DIR)/libmlx42.a
NAME = minirt
NAME_BONUS = minirt_bonus
LIBFT = $(LIB_DIR)/libft.a
GNL = $(LIB_DIR)/libgnl.a
MLX_FLAG = -ldl -lglfw -pthread -lm 

SRC = src/calculate2.c src/color.c src/get_normal.c src/parse.c src/parse_utils2.c src/ray_cylinder2.c src/ray_cylinder.c src/ray_sphere.c src/reserve_obj.c \
src/calculate.c src/free.c src/free2.c src/main.c src/parse_objs.c src/parse_utils.c src/ray_plane.c src/reserve.c \
src/reserve_utils.c src/vector_math.c src/parse_utils3.c src/vector_math2.c src/collisions.c

BONUS = src_bonus/calculate2.c src_bonus/color.c src_bonus/get_normal.c src_bonus/parse.c src_bonus/parse_utils2.c \
src_bonus/ray_cylinder2.c src_bonus/ray_cylinder.c src_bonus/ray_sphere.c src_bonus/reserve_obj.c \
src_bonus/calculate.c src_bonus/free.c src/free2.c src_bonus/main.c src_bonus/parse_objs.c src_bonus/parse_utils.c src_bonus/ray_plane.c src_bonus/reserve.c \
src_bonus/reserve_utils.c src_bonus/vector_math.c src_bonus/parse_utils3.c src_bonus/vector_math2.c src_bonus/collisions.c

OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(INCLUDE) $(MLX_A) -o $(NAME) $(MLX_FLAG) $(LIBFT) $(GNL)

%.o: %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_BONUS)
	$(CC) $(FLAGS) $(OBJS_BONUS) $(INCLUDE) $(MLX_A) -o $(NAME_BONUS) $(MLX_FLAG) $(LIBFT) $(GNL)

clean:
	rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all
