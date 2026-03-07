NAME        := cub3D

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -Iincludes -Iget_next_line

SRCS        := \
	src/main.c \
	src/parsing.c \
	src/init_struct.c \
	src/init_utils.c \
	src/string_dup.c \
	src/init_read.c \
	src/init_map.c \
	src/find_player.c \
	src/parse_cub.c \
	src/good_map.c \
	src/good_map_utils.c \
	src/good_map_push.c \
	src/good_map_cfg.c \
	src/good_map_rgb.c \
	src/good_map_grid.c \
	src/map_get.c \
	src/mlx_init.c \
	src/pixel.c \
	src/render.c \
	src/raycast.c \
	src/input.c \
	src/cleanup.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

SRCS_BONUS  :=

OBJDIR      := obj
OBJS        := $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS  := $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)

BONUS_NAME  := $(NAME)_bonus

RM          := rm -f
RMDIR       := rm -rf

# ---- MiniLibX ----
MLX_DIR     := minilibx-linux
MLX_LIB     := $(MLX_DIR)/libmlx.a

UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	INCLUDES    += -I/opt/X11/include
	MLX_FLAGS   := -L$(MLX_DIR) -lmlx -L/opt/X11/lib -lXext -lX11 -lm
else
	MLX_FLAGS   := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
endif

# ------------------

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
