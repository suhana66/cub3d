NAME := libft.a
SRC := ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isprint.c \
	ft_isascii.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strlen.c \
	is_allspaces.c\
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_strjoin.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_substr.c \
	ft_strtrim.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_split.c \
	ft_striteri.c \
	ft_strmapi.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memset.c \
	ft_memmove.c \
	ft_atoi.c \
	ft_itoa.c \
	ft_bzero.c \
	ft_calloc.c
SRC_B = ft_lstnew.c \
	ft_lstlast.c \
	ft_lstsize.c \
	ft_lstadd_front.c \
	ft_lstadd_back.c \
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c
OBJ := $(SRC:.c=.o)
OBJ_B := $(SRC_B:.c=.o)
CC := cc
CFLAGS := -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

bonus: $(OBJ) $(OBJ_B)
	ar rcs $(NAME) $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)

fclean: clean
	rm -f $(NAME)

re: fclean all
