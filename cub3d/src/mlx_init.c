/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/03/07 03:22:24 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	load_texture(void *mlx, t_img *tex, char *path, char *name)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->w, &tex->h);
	if (!tex->img)
		return (print_error(name));
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (print_error(name));
	return (1);
}

static int	setup_mlx_core(t_game *g, int w, int h, char *title)
{
	g->mlx.w = w;
	g->mlx.h = h;
	g->mlx.mlx = mlx_init();
	if (!g->mlx.mlx)
		return (print_error("mlx initialization failed"));
	g->mlx.win = mlx_new_window(g->mlx.mlx, w, h, title);
	if (!g->mlx.win)
		return (print_error("window creation failed"));
	g->mlx.frame.img = mlx_new_image(g->mlx.mlx, w, h);
	if (!g->mlx.frame.img)
		return (print_error("frame allocation failed"));
	g->mlx.frame.addr = mlx_get_data_addr(g->mlx.frame.img,
			&g->mlx.frame.bpp, &g->mlx.frame.line_len, &g->mlx.frame.endian);
	if (!g->mlx.frame.addr)
		return (print_error("frame data initialization failed"));
	return (1);
}

static void	destroy_images(t_game *g)
{
	if (g->mlx.mlx && g->mlx.frame.img)
		mlx_destroy_image(g->mlx.mlx, g->mlx.frame.img);
	if (g->mlx.mlx && g->tex_no.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_no.img);
	if (g->mlx.mlx && g->tex_so.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_so.img);
	if (g->mlx.mlx && g->tex_we.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_we.img);
	if (g->mlx.mlx && g->tex_ea.img)
		mlx_destroy_image(g->mlx.mlx, g->tex_ea.img);
}

int	mlx_setup(t_game *g, int w, int h, char *title)
{
	if (!g)
		return (0);
	if (!setup_mlx_core(g, w, h, title))
		return (mlx_destroy(g), 0);
	if (!load_texture(g->mlx.mlx, &g->tex_no, g->cub.tex.north,
			"north texture loading failed"))
		return (mlx_destroy(g), 0);
	if (!load_texture(g->mlx.mlx, &g->tex_so, g->cub.tex.south,
			"south texture loading failed"))
		return (mlx_destroy(g), 0);
	if (!load_texture(g->mlx.mlx, &g->tex_we, g->cub.tex.west,
			"west texture loading failed"))
		return (mlx_destroy(g), 0);
	if (!load_texture(g->mlx.mlx, &g->tex_ea, g->cub.tex.east,
			"east texture loading failed"))
		return (mlx_destroy(g), 0);
	return (1);
}

void	mlx_destroy(t_game *g)
{
	if (!g)
		return ;
	destroy_images(g);
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
	g->tex_no.img = NULL;
	g->tex_so.img = NULL;
	g->tex_we.img = NULL;
	g->tex_ea.img = NULL;
}
