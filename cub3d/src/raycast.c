/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

#define FOV (M_PI / 3.0)

void	cast_rays(t_game *g)
{
	int		w;
	int		h;
	int		x;

	if (!g)
		return ;
	w = g->mlx.w;
	h = g->mlx.h;
	x = 0;
	while (x < w)
	{
		double	camera_x;
		double	ray_angle;
		double	ray_dir_x;
		double	ray_dir_y;
		int		map_x;
		int		map_y;
		double	delta_dist_x;
		double	delta_dist_y;
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit;
		int		side;
		int		max_steps;
		double	perp;
		int		line_h;
		int		draw_start;
		int		draw_end;
		int		draw_start_raw;
		double	wall_x;
		int		tex_x;
		int		tex_y;
		double	tex_pos;
		double	tex_step;
		int		y;

		camera_x = (2.0 * x / (double)w) - 1.0;
		ray_angle = g->player.angle + atan(camera_x * tan(FOV / 2.0));
		ray_dir_x = cos(ray_angle);
		ray_dir_y = sin(ray_angle);
		map_x = (int)g->player.x;
		map_y = (int)g->player.y;
		delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1.0 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1.0 / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (g->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - g->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (g->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - g->player.y) * delta_dist_y;
		}
		hit = 0;
		side = 0;
		max_steps = g->cub.map.width * g->cub.map.height + 256;
		if (max_steps < 256)
			max_steps = 256;
		while (!hit && max_steps-- > 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_is_wall(&g->cub.map, map_x, map_y))
				hit = 1;
		}
		if (side == 0)
			perp = (map_x - g->player.x + (1 - step_x) / 2.0) / ray_dir_x;
		else
			perp = (map_y - g->player.y + (1 - step_y) / 2.0) / ray_dir_y;
		if (perp < 0.0001)
			perp = 0.0001;
		line_h = (int)(h / perp);
		if (line_h < 1)
			line_h = 1;
		draw_start_raw = -line_h / 2 + h / 2;
		draw_start = draw_start_raw;
		draw_end = line_h / 2 + h / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= h)
			draw_end = h - 1;
		if (side == 0)
			wall_x = g->player.y + perp * ray_dir_y;
		else
			wall_x = g->player.x + perp * ray_dir_x;
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * g->wall_tex.w);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = g->wall_tex.w - tex_x - 1;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= g->wall_tex.w)
			tex_x = g->wall_tex.w - 1;
		tex_step = (double)g->wall_tex.h / (double)line_h;
		tex_pos = (draw_start - draw_start_raw) * tex_step;
		y = draw_start;
		while (y <= draw_end)
		{
			if (g->wall_tex.addr && line_h > 0)
			{
				tex_y = (int)tex_pos;
				if (tex_y < 0)
					tex_y = 0;
				if (tex_y >= g->wall_tex.h)
					tex_y = g->wall_tex.h - 1;
				put_pixel(g, x, y, *(int *)(g->wall_tex.addr + tex_y
						* g->wall_tex.line_len + tex_x * (g->wall_tex.bpp / 8)));
				tex_pos += tex_step;
			}
			else
				put_pixel(g, x, y, 0x00AA00);
			y++;
		}
		x++;
	}
}
