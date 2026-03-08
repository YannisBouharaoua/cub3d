/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/03/07 02:52:10 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MOVE_SPEED 0.03
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

static void	move_player(t_game *g, double fwd, double strafe)
{
	double	nx;
	double	ny;
	double	strafe_a;

	nx = g->player.x + cos(g->player.angle) * fwd;
	ny = g->player.y + sin(g->player.angle) * fwd;
	strafe_a = g->player.angle + (PI / 2.0);
	nx += cos(strafe_a) * strafe;
	ny += sin(strafe_a) * strafe;
	if (can_move(g, nx, g->player.y))
		g->player.x = nx;
	if (can_move(g, g->player.x, ny))
		g->player.y = ny;
}

static void	update_player(t_game *g)
{
	double	fwd;
	double	strafe;
	double	rot;

	fwd = (g->keys[ACT_MOVE_FWD] - g->keys[ACT_MOVE_BACK]) * MOVE_SPEED;
	strafe = (g->keys[ACT_MOVE_RIGHT] - g->keys[ACT_MOVE_LEFT]) * MOVE_SPEED;
	rot = (g->keys[ACT_TURN_RIGHT] - g->keys[ACT_TURN_LEFT]) * ROT_SPEED;
	g->player.angle += rot;
	move_player(g, fwd, strafe);
}

void	draw_floor_ceiling(t_game *g)
{
	int	x;
	int	y;
	int	half;

	if (!g)
		return ;
	half = g->mlx.h / 2;
	y = 0;
	while (y < half)
	{
		x = 0;
		while (x < g->mlx.w)
			put_pixel(g, x++, y, g->ceil_color);
		y++;
	}
	while (y < g->mlx.h)
	{
		x = 0;
		while (x < g->mlx.w)
			put_pixel(g, x++, y, g->floor_color);
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
