NAME        := cub3D

CC          := cc
CFLAGS      := -Wall -Wextra -Werror

INCLUDES    := -Iincludes -Iget_next_line

SRCS        := \
	src/engine_mmestron/main.c \
	src/engine_mmestron/init_game_struct.c \
	src/engine_mmestron/input.c \
	src/engine_mmestron/map_get.c \
	src/engine_mmestron/mlx_init.c \
	src/engine_mmestron/pixel.c \
	src/engine_mmestron/render.c \
	src/engine_mmestron/raycast.c \
	src/parsing_yabouhar/parsing.c \
	src/parsing_yabouhar/init_cub.c \
	src/parsing_yabouhar/init_utils.c \
	src/parsing_yabouhar/string_dup.c \
	src/parsing_yabouhar/init_read.c \
	src/parsing_yabouhar/init_map.c \
	src/parsing_yabouhar/find_player.c \
	src/parsing_yabouhar/parse_cub.c \
	src/parsing_yabouhar/good_map.c \
	src/parsing_yabouhar/good_map_utils.c \
	src/parsing_yabouhar/good_map_push.c \
	src/parsing_yabouhar/good_map_cfg.c \
	src/parsing_yabouhar/good_map_rgb.c \
	src/parsing_yabouhar/good_map_grid.c \
	src/parsing_yabouhar/cleanup.c \
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
