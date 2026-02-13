/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100

#define MOVE_SPEED 0.06
#define ROT_SPEED 0.04
#define COLLIDER_R 0.20

static int	can_move(t_game *g, double x, double y)
{
	if (map_is_wall(&g->cub.map, (int)(x - COLLIDER_R), (int)(y - COLLIDER_R)))
		return (0);
	if (map_is_wall(&g->cub.map, (int)(x + COLLIDER_R), (int)(y - COLLIDER_R)))
		return (0);
	if (map_is_wall(&g->cub.map, (int)(x - COLLIDER_R), (int)(y + COLLIDER_R)))
		return (0);
	if (map_is_wall(&g->cub.map, (int)(x + COLLIDER_R), (int)(y + COLLIDER_R)))
		return (0);
	return (1);
}

static void	update_player(t_game *g)
{
	double	move;
	double	rot;
	double	nx;
	double	ny;

	move = (g->keys[KEY_W] - g->keys[KEY_S]) * MOVE_SPEED;
	rot = (g->keys[KEY_D] - g->keys[KEY_A]) * ROT_SPEED;
	g->player.angle += rot;
	nx = g->player.x + cos(g->player.angle) * move;
	ny = g->player.y + sin(g->player.angle) * move;
	if (can_move(g, nx, g->player.y))
		g->player.x = nx;
	if (can_move(g, g->player.x, ny))
		g->player.y = ny;
}

static int	img_get_pixel(t_img *img, int x, int y)
{
	int		*px;

	if (!img || !img->addr || img->w <= 0 || img->h <= 0)
		return (0);
	x = ((x % img->w) + img->w) % img->w;
	y = ((y % img->h) + img->h) % img->h;
	px = (int *)(img->addr + y * img->line_len + x * (img->bpp / 8));
	return (*px);
}

void	draw_floor_ceiling(t_game *g)
{
	int	x;
	int	y;
	int	half;
	int	fx;
	int	fy;

	if (!g)
		return ;
	half = g->mlx.h / 2;
	y = 0;
	while (y < g->mlx.h)
	{
		x = 0;
		while (x < g->mlx.w)
		{
			if (y < half)
				put_pixel(g, x, y, g->ceil_color);
			else if (g->floor_tex.addr)
			{
				fx = x / 2;
				fy = (y - half) / 2;
				put_pixel(g, x, y, img_get_pixel(&g->floor_tex, fx, fy));
			}
			else
				put_pixel(g, x, y, g->floor_color);
			x++;
		}
		y++;
	}
}

int	render_frame(t_game *g)
{
	if (!g)
		return (0);
	update_player(g);
	draw_floor_ceiling(g);
	cast_rays(g);
	mlx_put_image_to_window(g->mlx.mlx, g->mlx.win, g->mlx.frame.img, 0, 0);
	return (0);
}
