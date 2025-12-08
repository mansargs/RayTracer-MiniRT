MAKEFLAGS += --no-print-directory --silent

# =============================
#          COLORS
# =============================
RESET   := \033[0m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE    := \033[34m
MAGENTA := \033[35m
CYAN    := \033[36m

# =============================
#        PROJECT SETTINGS
# =============================
NAME        = miniRT
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

SRC_DIR     = srcs
OBJ_DIR     = objects
LIB_DIR     = libraries

LIBFT_DIR   = $(LIB_DIR)/libft
GNL_DIR     = $(LIB_DIR)/gnl
MLX_DIR     = $(LIB_DIR)/mlx

LIBFT       = $(LIBFT_DIR)/libft.a
GNL         = $(GNL_DIR)/gnl.a
MLX         = $(MLX_DIR)/libmlx.a

INCS        = -I hdrs \
              -I $(LIBFT_DIR) \
              -I $(GNL_DIR) \
              -I $(MLX_DIR)/include

# =============================
#         SOURCE FILES
# =============================
SRCS = \
	$(SRC_DIR)/main.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# =============================
#          MAIN TARGETS
# =============================

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJS)
	@echo "$(CYAN)[Linking]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(MLX)
	@echo "$(GREEN)Build complete ✔$(RESET)"

# =============================
#        COMPILATION RULE
# =============================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)[Compiling]$(RESET) $<"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# =============================
#         LIBRARY RULES
# =============================

$(LIBFT):
	@echo "$(MAGENTA)[Building Libft]$(RESET)"
	@$(MAKE) bonus -C $(LIBFT_DIR) > /dev/null 2>&1

$(GNL):
	@echo "$(MAGENTA)[Building GNL]$(RESET)"
	@$(MAKE) -C $(GNL_DIR) > /dev/null 2>&1

$(MLX):
	@echo "$(MAGENTA)[Building MLX]$(RESET)"
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "$(YELLOW)Configuring MLX silently...$(RESET)"; \
		cd $(MLX_DIR) && ./configure > /dev/null 2>&1; \
	fi
	@cd $(MLX_DIR) && $(MAKE) -s > /dev/null 2>&1


# =============================
#              CLEAN
# =============================

clean:
	@echo "$(YELLOW)[Cleaning objects]$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(GNL_DIR)
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then \
		$(MAKE) clean -C $(MLX_DIR); \
	else \
		echo "$(YELLOW)Skipping MLX clean (not configured).$(RESET)"; \
	fi

fclean: clean
	@echo "$(YELLOW)[Removing executable]$(RESET)"
	@$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) fclean -C $(GNL_DIR)

re: fclean all

.PHONY: all clean fclean re
