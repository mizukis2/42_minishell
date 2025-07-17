NAME = libft.a
HEADERS = ../include/libft.h
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c \
       ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_split.c ft_strchr.c ft_strdup.c ft_strndup.c \
       ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
       ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_itoa.c ft_strmapi.c ft_striteri.c \
       ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
        ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_printf_helpers.c ft_printf.c get_next_line.c get_next_line_utils.c \
        ft_strcmp.c ft_strstr.c ft_putstr.c

OBJS = $(SRCS:.c=.o)

# Default rule to build the library
all: $(NAME)

# Rule for creating the library archive
$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

# Rule for compiling .c into .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up object files
clean:
	rm -f $(OBJS)

# Clean up all generated files
fclean: clean
	rm -f $(NAME)

# Rebuild the library from scratch
re: fclean all

.PHONY: all clean fclean re
