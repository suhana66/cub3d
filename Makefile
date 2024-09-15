NAME := cub3D
CC := cc
CFLAGS := -Wall -Wextra -Werror -Wfatal-errors

GNL := GNL/get_next_line.c \
	GNL/get_next_line_utils.c
PARSING := parsing/colors_parsing.c \
	parsing/custom_trim.c \
	parsing/line_utils.c \
	parsing/map_parsing.c \
	parsing/parse_input.c \
	parsing/store_validate.c \
	parsing/str_to_int.c \
	parsing/textures_parsing.c
EXECUTION := execution/draw.c \
	execution/hooks.c \
	execution/raycasting.c \
	execution/utils.c
SRC := main.c \
	memory_management.c \
	$(GNL) \
	$(PARSING) \
	$(EXECUTION)
OBJ := $(SRC:.c=.o)

LIBFT_PATH := libft
LIBFT := $(LIBFT_PATH)/libft.a
LIBFT_LINK := -L$(LIBFT_PATH) -lft

LIBMLX_PATH := libmlx
LIBMLX := $(LIBMLX_PATH)/libmlx.a
LIBMLX_LINK := -L$(LIBMLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(LIBMLX)
	$(CC) -fsanitize=address -g3 $(CFLAGS) $(OBJ) -lm $(LIBFT_LINK) $(LIBMLX_LINK) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBMLX_PATH) -I$(LIBFT_PATH) -IGNL -I. -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

$(LIBMLX):
	make -C $(LIBMLX_PATH)

clean:
	make fclean -C $(LIBFT_PATH)
	make clean -C $(LIBMLX_PATH)
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
