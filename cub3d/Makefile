NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -Iincludes -Iget_next_line

SRCS = \
	src/main.c \
	src/parsing.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

SRCS_BONUS =

OBJDIR = obj
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
OBJS_BONUS = $(SRCS_BONUS:%.c=$(OBJDIR)/%.o)
BONUS_NAME = $(NAME)_bonus

RM = rm -f
RMDIR = rm -rf

MLX_DIR =
MLX_FLAGS =
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd
else ifeq ($(UNAME_S),Darwin)
MLX_DIR = minilibx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
endif

ifneq ($(strip $(MLX_DIR)),)
MLX_LIB := $(MLX_DIR)/libmlx.a
MLX_AVAILABLE := $(shell test -f $(MLX_LIB) -o -f $(MLX_DIR)/Makefile && echo yes)
ifneq ($(MLX_AVAILABLE),)
LDLIBS += $(MLX_FLAGS)
MLX_TARGET := $(MLX_LIB)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)
endif
endif

all: $(NAME)

$(NAME): $(OBJS) $(MLX_TARGET)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(OBJS) $(OBJS_BONUS) $(MLX_TARGET)
	$(CC) $(CFLAGS) $(OBJS) $(OBJS_BONUS) $(LDLIBS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	$(RMDIR) $(OBJDIR)
	@if [ -n "$(MLX_AVAILABLE)" ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)
	@if [ -n "$(MLX_AVAILABLE)" ]; then $(MAKE) -C $(MLX_DIR) fclean; fi

re: fclean all

.PHONY: all bonus clean fclean re
