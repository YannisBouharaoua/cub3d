/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 14:28:14 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/13 14:55:45 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static double	dir_to_angle(char c)
{
	const double	pi = 3.14159265358979323846;

	if (c == 'N')
		return (-pi / 2.0);
	if (c == 'S')
		return (pi / 2.0);
	if (c == 'W')
		return (pi);
	return (0.0);
}

int	main(int ac, char **av)
{
	t_game	g;
	char	*path;

	if (ac < 2)
	{
		fprintf(stderr, "Usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	path = av[1];
	if (!not_directory(path))
	{
		fprintf(stderr, "Is a Directory\n");
		return (1);
	}
	// if (!good_map(path))
	// {
	// 	fprintf(stderr, "BadMap Format\n");
	// 	return (1);
	// }
	memset(&g, 0, sizeof(g));
	init_map(&g.cub.map, path);
	g.player.x = g.cub.map.player_x + 0.5;
	g.player.y = g.cub.map.player_y + 0.5;
	g.player.angle = dir_to_angle(g.cub.map.player_dir);
	g.ceil_color = 0x777777;
	g.floor_color = 0x222222;
	if (!mlx_setup(&g, 1024, 768, "cub3D"))
		return (1);
	mlx_hook(g.mlx.win, 2, 1L << 0, key_press, &g);
	mlx_hook(g.mlx.win, 3, 1L << 1, key_release, &g);
	mlx_hook(g.mlx.win, 17, 0, on_close, &g);
	mlx_loop_hook(g.mlx.mlx, render_frame, &g);
	mlx_loop(g.mlx.mlx);
	mlx_destroy(&g);
	return (0);
}
