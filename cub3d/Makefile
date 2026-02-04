NAME        := cub3D

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -Iincludes -Iget_next_line

SRCS        := \
	src/main.c \
	src/parsing.c \
	src/init_struct.c \
	src/good_map.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

SRCS_BONUS  :=

OBJDIR      := obj
OBJS        := $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS  := $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)

BONUS_NAME  := $(NAME)_bonus

RM          := rm -f
RMDIR       := rm -rf

# ---- MiniLibX (Ubuntu / Linux) ----
MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a
MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# -----------------------------------

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS) $(OBJS_BONUS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(MLX_FLAGS) -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RMDIR) $(OBJDIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
