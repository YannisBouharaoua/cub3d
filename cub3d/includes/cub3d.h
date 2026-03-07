/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:25:53 by yabouhar          #+#    #+#             */
/*   Updated: 2026/03/07 03:08:57 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"

# define PI 3.14159265358979323846

# define ACT_MOVE_FWD 0
# define ACT_MOVE_LEFT 1
# define ACT_MOVE_BACK 2
# define ACT_MOVE_RIGHT 3
# define ACT_TURN_LEFT 4
# define ACT_TURN_RIGHT 5

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	player_dir;
	int		player_x;
	int		player_y;
}	t_map;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_texture;

typedef struct s_cub
{
	t_texture	tex;
	t_color		floor;
	t_color		ceiling;
	t_map		map;
}	t_cub;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	double	perp;
	double	wall_x;
	double	step;
	double	pos;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		side;
	int		line_h;
	int		start;
	int		end;
	int		tex_x;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;
	t_img	frame;
}	t_mlx;

typedef struct s_game
{
	t_cub		cub;
	t_mlx		mlx;
	t_player	player;
	t_img		tex_no;
	t_img		tex_so;
	t_img		tex_we;
	t_img		tex_ea;
	int			floor_color;
	int			ceil_color;
	int			keys[1024];
}	t_game;

typedef struct s_flood
{
	char	**g;
	int		h;
	int		w;
}	t_flood;

typedef struct s_gm
{
	t_cub	*cub;
	int		fd;
	char	*line;
	int		in_map;
	int		player_count;
	int		width;
	int		height;
	int		cap;
	char	**lines;
	char	**pad;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
}	t_gm;

int		not_directory(char *str);
int		parse_cub(t_cub *cub, char *path_map);
int		good_map(char *path_map);
void	init_cub(t_cub *cub);
void	init_game_struct(t_game *game);
void	free_cub(t_cub *cub);
void	free_map_grid(t_map *map);

int		is_map_line(char *line);
int		is_empty_line(char *line);
size_t	str_len(const char *s);
char	*str_dup(const char *s);
char	*str_ndup(const char *s, size_t len);
char	*str_chr(const char *s, int c);
int		print_error(char *msg);
void	gnl_clear(void);
int		read_cub_file(t_gm *gm);
int		build_map(t_gm *gm);
int		find_player(t_map *map);

int		gm_has_cub_ext(const char *s);
int		gm_is_config_line(char *line);
int		gm_parse_config(char *line, t_gm *gm);
int		gm_set_color(t_color *color, int *flag, char *s);
void	gm_free_lines(char **lines, int count);
int		gm_push_line(char ***lines, int *count, int *cap, char *line);
char	**gm_pad_lines(char **lines, int height, int width);
int		gm_is_closed(char **lines, int height, int width);

int		mlx_setup(t_game *g, int w, int h, char *title);
void	mlx_destroy(t_game *g);

int		render_frame(t_game *g);
void	put_pixel(t_game *g, int x, int y, int color);
void	draw_floor_ceiling(t_game *g);

char	map_get(t_map *m, int mx, int my);
int		map_is_wall(t_map *m, int mx, int my);

void	cast_rays(t_game *g);

int		key_press(int keycode, t_game *g);
int		key_release(int keycode, t_game *g);
int		on_close(t_game *g);

#endif
