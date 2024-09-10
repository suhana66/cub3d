NAME := cub3d
CC := cc
CFLAGS := -Wall -Wextra -Werror

SRC := main.c
OBJ := $(SRC:.c=.o)

LIBMLX_PATH := libmlx
LIBMLX := $(LIBMLX_PATH)/libmlx.a
LIBMLX_LINK := -L$(LIBMLX_PATH) -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLX)
	$(CC) $(CFLAGS) $(OBJ) -lm $(LIBMLX_LINK) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBMLX_PATH) -c $< -o $@

$(LIBMLX):
	make -C $(LIBMLX_PATH)

clean:
	rm -f $(OBJ)

fclean: clean
	make clean -C $(LIBMLX_PATH)
	rm -f $(NAME)

re: fclean all
	
.PHONY: all clean fclean re