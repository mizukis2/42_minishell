NAME =							minishell

CC =							cc
CFLAGS =						-Wall -Werror -Wextra -I ./include -I libft

SRC_DIR =						src
OBJ_DIR =						obj
LIBFT_DIR =						libft
LIBFT =							$(LIBFT_DIR)/libft.a

SRCS = 							\
								src/main/main.c \
								src/main/shell_utils.c \
								src/main/shell_loop.c \
								src/lexer/lexer.c \
								src/lexer/lexer_utils.c \
								src/lexer/lexer_states.c \
								src/lexer/token_utils.c \
								src/parser/parser.c \
								src/parser/parse_types.c \
								src/env/copy_initial_env.c \
								src/env/list_to_array.c \
								src/env/env_utils.c \
								src/env/update_env.c \

OBJS = 							$(patsubst %.c, $(OBJ_DIR)/%.o, $(subst $(SRC_DIR)/,,$(SRCS)))
LIBS =							-L$(LIBFT_DIR) -lft -lreadline


GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RESET = \033[0m

all:							$(NAME)

$(NAME):						$(LIBFT) $(OBJS)
								@echo "$(GREEN)...Compiling Minishell...$(RESET)"
								@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
								@echo "$(GREEN) --- Minishell Compiled --- $(RESET)"

$(OBJ_DIR)/%.o:					$(SRC_DIR)/%.c
								@mkdir -p $(dir $@)
								@$(CC) $(CFLAGS) -c $< -o $@



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