/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/03/07 03:27:17 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	init_ray(t_game *g, t_ray *r, int x)
{
	double	camera_x;
	double	angle;

	camera_x = (2.0 * x / (double)g->mlx.w) - 1.0;
	angle = g->player.angle + atan(camera_x * tan(PI / 6.0));
	r->ray_dir_x = cos(angle);
	r->ray_dir_y = sin(angle);
	r->map_x = (int)g->player.x;
	r->map_y = (int)g->player.y;
	r->delta_x = fabs(1.0 / (r->ray_dir_x + (r->ray_dir_x == 0) * 1e-9));
	r->delta_y = fabs(1.0 / (r->ray_dir_y + (r->ray_dir_y == 0) * 1e-9));
	r->step_x = 1;
	r->step_y = 1;
	r->side_x = (r->map_x + 1.0 - g->player.x) * r->delta_x;
	r->side_y = (r->map_y + 1.0 - g->player.y) * r->delta_y;
	if (r->ray_dir_x < 0)
		r->step_x = -1;
	if (r->ray_dir_x < 0)
		r->side_x = (g->player.x - r->map_x) * r->delta_x;
	if (r->ray_dir_y < 0)
		r->step_y = -1;
	if (r->ray_dir_y < 0)
		r->side_y = (g->player.y - r->map_y) * r->delta_y;
}

static void	step_dda(t_game *g, t_ray *r)
{
	int	steps;

	steps = g->cub.map.width * g->cub.map.height + 256;
	r->side = 0;
	while (steps-- > 0)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (map_is_wall(&g->cub.map, r->map_x, r->map_y))
			return ;
	}
}

static t_img	*compute_wall(t_game *g, t_ray *r)
{
	if (r->side == 0)
		r->perp = (r->map_x - g->player.x + (1 - r->step_x) / 2.0)
			/ r->ray_dir_x;
	else
		r->perp = (r->map_y - g->player.y + (1 - r->step_y) / 2.0)
			/ r->ray_dir_y;
	if (r->perp < 0.0001)
		r->perp = 0.0001;
	r->line_h = (int)(g->mlx.h / r->perp);
	r->start = -r->line_h / 2 + g->mlx.h / 2;
	r->end = r->line_h / 2 + g->mlx.h / 2;
	if (r->start < 0)
		r->start = 0;
	if (r->end >= g->mlx.h)
		r->end = g->mlx.h - 1;
	if (r->side == 0 && r->step_x > 0)
		return (&g->tex_ea);
	if (r->side == 0 && r->step_x < 0)
		return (&g->tex_we);
	if (r->side == 1 && r->step_y > 0)
		return (&g->tex_so);
	return (&g->tex_no);
}

static void	draw_column(t_game *g, t_ray *r, t_img *tex, int x)
{
	int	y;
	int	tex_y;

	r->wall_x = g->player.x + r->perp * r->ray_dir_x;
	if (r->side == 0)
		r->wall_x = g->player.y + r->perp * r->ray_dir_y;
	r->wall_x -= floor(r->wall_x);
	r->tex_x = (int)(r->wall_x * tex->w);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		r->tex_x = tex->w - r->tex_x - 1;
	r->step = (double)tex->h / (double)r->line_h;
	r->pos = (r->start + r->line_h / 2 - g->mlx.h / 2) * r->step;
	y = r->start;
	while (y <= r->end)
	{
		tex_y = (int)r->pos;
		if (tex->addr)
			put_pixel(g, x, y, *(int *)(tex->addr + tex_y * tex->line_len
					+ r->tex_x * (tex->bpp / 8)));
		r->pos += r->step;
		y++;
	}
}

void	cast_rays(t_game *g)
{
	int		x;
	t_ray	r;
	t_img	*tex;

	x = 0;
	while (x < g->mlx.w)
	{
		init_ray(g, &r, x);
		step_dda(g, &r);
		tex = compute_wall(g, &r);
		draw_column(g, &r, tex, x);
		x++;
	}
}
