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

PARSING     = $(SRC_DIR)/parsing
PARSING_ELEM = $(PARSING)/elements
PARSING_VAL = $(PARSING)/validation
PARSING_UTL = $(PARSING)/parsing_utils
CONTAINER   = $(SRC_DIR)/container
UTILS       = $(SRC_DIR)/utils
VEC_MATHS   = $(SRC_DIR)/vec_maths
RAY_TRACING = $(SRC_DIR)/ray_tracing
DRAWING     = $(SRC_DIR)/drawing

LIBFT_DIR   = $(LIB_DIR)/libft
GNL_DIR     = $(LIB_DIR)/gnl
MLX_DIR     = $(LIB_DIR)/mlx

LIBFT       = $(LIBFT_DIR)/libft.a
GNL         = $(GNL_DIR)/gnl.a
MLX         = $(MLX_DIR)/libmlx.a

INCS        = -I hdrs \
              -I $(SRC_DIR) \
              -I $(PARSING_VAL) \
			  -I $(PARSING_ELEM) \
			  -I $(PARSING_UTL) \
			  -I $(RAY_TRACING)/intersection \
              -I $(LIBFT_DIR) \
              -I $(GNL_DIR) \
              -I $(MLX_DIR)

MLX_FLAGS = -lX11 -lXext -lm

# =============================
#         SOURCE FILES
# =============================
SRCS = \
	$(SRC_DIR)/main.c \
	$(PARSING)/identifier.c \
	$(PARSING_ELEM)/parse_ambient.c \
	$(PARSING_ELEM)/parse_camera.c \
	$(PARSING_ELEM)/parse_lights.c \
	$(PARSING_ELEM)/parse_spheres.c \
	$(PARSING_ELEM)/parse_planes.c \
	$(PARSING_ELEM)/parse_cones.c \
	$(PARSING_ELEM)/parse_cylinders.c \
	$(PARSING_ELEM)/parse_optional.c \
	$(PARSING_VAL)/validation_part1.c \
	$(PARSING_VAL)/validation_part2.c \
	$(PARSING_UTL)/parse_helpers.c \
	$(PARSING_UTL)/helpers.c \
	$(CONTAINER)/vector.c \
	$(UTILS)/free.c $(UTILS)/init.c \
	$(VEC_MATHS)/vec_arithmetic.c \
	$(VEC_MATHS)/vec_magnitude.c \
	$(VEC_MATHS)/vec_normalized.c \
	$(RAY_TRACING)/ray_trace/ray_generation.c \
	$(RAY_TRACING)/ray_trace/ray_trace.c \
	$(RAY_TRACING)/intersection/intersection.c \
	$(RAY_TRACING)/intersection/intersection_spheres.c \
	$(RAY_TRACING)/intersection/interspection_planes.c \
	$(RAY_TRACING)/intersection/quadratic.c \
	$(DRAWING)/window.c


OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# =============================
#          MAIN TARGETS
# =============================

all: $(NAME)

$(NAME): $(LIBFT) $(GNL) $(MLX) $(OBJS)
	@echo "$(CYAN)[Linking]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(LIBFT) $(GNL) $(MLX) $(MLX_FLAGS)
	@echo "$(GREEN)Build complete ✔$(RESET)"

# =============================
#        COMPILATION RULE
# =============================

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)[Compiling]$(RESET)"
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@

# =============================
#         LIBRARY RULES
# =============================

$(LIBFT):
	@echo "$(MAGENTA)[Building Libft]$(RESET)"
	@$(MAKE) bonus -C $(LIBFT_DIR)

$(GNL):
	@echo "$(MAGENTA)[Building GNL]$(RESET)"
	@$(MAKE) -C $(GNL_DIR)

$(MLX):
	@echo "$(MAGENTA)[Building MLX]$(RESET)"
	@if [ ! -f $(MLX_DIR)/Makefile.gen ]; then \
		echo "$(YELLOW)Configuring MLX silently...$(RESET)"; \
		cd $(MLX_DIR) && ./configure > /dev/null 2>&1; \
	fi
	@cd $(MLX_DIR) && $(MAKE) > /dev/null 2>&1


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
