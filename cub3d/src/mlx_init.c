/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	fail(const char *msg)
{
	perror(msg);
	return (0);
}

int	mlx_setup(t_game *g, int w, int h, char *title)
{
	if (!g)
		return (0);
	g->mlx.w = w;
	g->mlx.h = h;
	g->mlx.mlx = mlx_init();
	if (!g->mlx.mlx)
		return (fail("mlx_init"));
	g->mlx.win = mlx_new_window(g->mlx.mlx, w, h, title);
	if (!g->mlx.win)
	{
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
		g->mlx.mlx = NULL;
		return (fail("mlx_new_window"));
	}
	g->mlx.frame.img = mlx_new_image(g->mlx.mlx, w, h);
	if (!g->mlx.frame.img)
	{
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
		g->mlx.mlx = NULL;
		g->mlx.win = NULL;
		return (fail("mlx_new_image"));
	}
	g->mlx.frame.w = w;
	g->mlx.frame.h = h;
	g->mlx.frame.addr = mlx_get_data_addr(g->mlx.frame.img,
			&g->mlx.frame.bpp, &g->mlx.frame.line_len, &g->mlx.frame.endian);
	if (!g->mlx.frame.addr)
	{
		mlx_destroy_image(g->mlx.mlx, g->mlx.frame.img);
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
		g->mlx.mlx = NULL;
		g->mlx.win = NULL;
		g->mlx.frame.img = NULL;
		return (fail("mlx_get_data_addr"));
	}
	g->wall_tex.img = mlx_xpm_file_to_image(g->mlx.mlx,
			"textures/01bricks1.xpm", &g->wall_tex.w, &g->wall_tex.h);
	if (!g->wall_tex.img)
		return (fail("wall texture"));
	g->wall_tex.addr = mlx_get_data_addr(g->wall_tex.img,
			&g->wall_tex.bpp, &g->wall_tex.line_len, &g->wall_tex.endian);
	g->floor_tex.img = mlx_xpm_file_to_image(g->mlx.mlx,
			"textures/04multia.xpm", &g->floor_tex.w, &g->floor_tex.h);
	if (!g->floor_tex.img)
		return (fail("floor texture"));
	g->floor_tex.addr = mlx_get_data_addr(g->floor_tex.img,
			&g->floor_tex.bpp, &g->floor_tex.line_len, &g->floor_tex.endian);
	return (1);
}

void	mlx_destroy(t_game *g)
{
	if (!g)
		return ;
	if (g->mlx.mlx && g->mlx.frame.img)
		mlx_destroy_image(g->mlx.mlx, g->mlx.frame.img);
	if (g->mlx.mlx && g->wall_tex.img)
		mlx_destroy_image(g->mlx.mlx, g->wall_tex.img);
	if (g->mlx.mlx && g->floor_tex.img)
		mlx_destroy_image(g->mlx.mlx, g->floor_tex.img);
	if (g->mlx.mlx && g->mlx.win)
		mlx_destroy_window(g->mlx.mlx, g->mlx.win);
	if (g->mlx.mlx)
	{
		mlx_destroy_display(g->mlx.mlx);
		free(g->mlx.mlx);
	}
	g->mlx.mlx = NULL;
	g->mlx.win = NULL;
	g->mlx.frame.img = NULL;
	g->mlx.frame.addr = NULL;
	g->wall_tex.img = NULL;
	g->wall_tex.addr = NULL;
	g->floor_tex.img = NULL;
	g->floor_tex.addr = NULL;
}
