/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:25:53 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 14:25:53 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

# include "../get_next_line/get_next_line.h"
# include "../minilibx-linux/mlx.h"

//Structure couleur RGB
typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

//Structure map
typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    char    player_dir;
    int     player_x;
    int     player_y;
}  t_map;

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
}   t_texture;

//Stucture CUB3D
typedef struct s_cub
{
    t_texture tex;
    t_color floor;
    t_color ceiling;
    t_map map;
}   t_cub;

typedef struct s_player
{
    double  x;
    double  y;
    double  angle;   // radians
}   t_player;

typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     w;
    int     h;
}   t_img;

typedef struct s_mlx
{
    void    *mlx;
    void    *win;
    int     w;
    int     h;
    t_img   frame;
}   t_mlx;

typedef struct s_game
{
    t_cub       cub;         // parsed data (map, textures, colors)
    t_mlx       mlx;         // runtime mlx handles
    t_player    player;      // runtime player state
    t_img       wall_tex;
    t_img       floor_tex;
    int         floor_color; // int 0xRRGGBB (temp)
    int         ceil_color;  // int 0xRRGGBB (temp)
    int         keys[1024];   // simple key state (optional)
}   t_game;

//PARSING
int		parsing(int ac, char **av);
int		not_directory(char *str);
void	init_map(t_map *map, char *path_map);
int		good_map(char *path_map);

// ENGINE (new)
int     mlx_setup(t_game *g, int w, int h, char *title);
void    mlx_destroy(t_game *g);

int     render_frame(t_game *g);
void    put_pixel(t_game *g, int x, int y, int color);
void    draw_floor_ceiling(t_game *g);

char    map_get(t_map *m, int mx, int my);
int     map_is_wall(t_map *m, int mx, int my);

void    cast_rays(t_game *g);

// INPUT
int     key_press(int keycode, t_game *g);
int     key_release(int keycode, t_game *g);
int     on_close(t_game *g);

#endif
