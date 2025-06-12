NAME =							minishell

CC =							cc
CFLAGS =						-Wall -Werror -Wextra $(HEADERS)
HEADERS =						-I ./include -I $(LIBFT_DIR)

SRC_DIR =						src
OBJ_DIR =						obj
LIBFT_DIR =						libft
LIBFT =							$(LIBFT_DIR)/libft.a

SRCS =							src/main.c src/cleaning.c
OBJS =							$(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBS =							-L$(LIBFT_DIR) -lft -lreadline

GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

all:							$(LIBFT) $(NAME)


$(OBJ_DIR)/%.o:					$(SRC_DIR)/%.c
								@mkdir -p $(OBJ_DIR)
								@$(CC) $(CFLAGS) -c $< -o $@

$(NAME):						$(OBJS) $(LIBFT)
								@echo "$(GREEN)...Compiling Minishell...$(RESET)"
								@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
								@echo "$(GREEN) --- Minishell Compiled --- $(RESET)"

$(LIBFT):
								@echo "$(BLUE)...Compiling Libft...$(RESET)"
								@make -s -C $(LIBFT_DIR)
								@echo "$(BLUE) --- Libft Compiled --- $(RESET)"

clean:
								@echo "$(YELLOW)...Cleaning in progress...$(RESET)"
								@rm -rf $(OBJ_DIR)
								@make -s -C $(LIBFT_DIR) clean
								@echo "$(YELLOW) --- Cleaning Done --- $(RESET)"

fclean:							clean
								@echo "$(YELLOW)...Deleting all...$(RESET)"
								@rm -rf $(NAME)
								@make -s -C $(LIBFT_DIR) fclean
								@echo "$(YELLOW) --- Deletion Done --- $(RESET)"

re:								fclean all

.PHONY:							all clean fclean re