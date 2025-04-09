NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0
RM = rm -rf

SRC_DIR = ./src
OBJ_DIR = ./obj
LIBFT_DIR = ./libft
MLX_DIR = ./minilibx-linux
INC_DIR = ./inc

LIBFT = $(LIBFT_DIR)/libft.a
MLX = $(MLX_DIR)/libmlx_Linux.a
# MLX = $(MLX_DIR)/libmlx_Darwin.a

LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -lX11 -lXext -lXrandr -lm
# LDFLAGS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -I/opt/X11/include -L/opt/X11/lib -lmlx -lX11 -lXext -lXrandr -lm
INC = -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(INC_DIR)

SRC = \
	$(SRC_DIR)/extract_img.c \
	$(SRC_DIR)/extract_map.c \
	$(SRC_DIR)/extract_str.c \
	$(SRC_DIR)/init_about_mlx.c \
	$(SRC_DIR)/print_parsed.c \
	$(SRC_DIR)/validate.c \
	$(SRC_DIR)/raycast.c \
	$(SRC_DIR)/render.c \
	$(SRC_DIR)/control.c \
	$(SRC_DIR)/memory.c \
	$(SRC_DIR)/free_both_case.c \
	$(SRC_DIR)/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(OBJ_DIR) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean


fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
# mlx에 fclean이 없음
# mlx.a를 여기서 어떻게 지우지?
# 대충 땜빵 했는데 이게 맞나?
	$(MAKE) -C $(MLX_DIR) clean
	$(RM) libmlx.a libmlx_Linux.a

re: fclean all

.PHONY: all clean fclean re
