/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:44:42 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:44:42 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static double	dir_to_angle(char c)
{
	if (c == 'N')
		return (-PI / 2.0);
	if (c == 'S')
		return (PI / 2.0);
	if (c == 'W')
		return (PI);
	return (0.0);
}

static void	setup_game(t_game *game)
{
	game->player.x = game->cub.map.player_x + 0.5;
	game->player.y = game->cub.map.player_y + 0.5;
	game->player.angle = dir_to_angle(game->cub.map.player_dir);
	game->ceil_color = (game->cub.ceiling.r << 16)
		| (game->cub.ceiling.g << 8) | game->cub.ceiling.b;
	game->floor_color = (game->cub.floor.r << 16)
		| (game->cub.floor.g << 8) | game->cub.floor.b;
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (print_error("usage: ./cub3D <map.cub>"), 1);
	init_game_struct(&game);
	if (!parse_cub(&game.cub, av[1]))
		return (1);
	setup_game(&game);
	if (!mlx_setup(&game, 1024, 768, "cub3D"))
	{
		mlx_destroy(&game);
		free_cub(&game.cub);
		return (1);
	}
	mlx_hook(game.mlx.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.mlx.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.mlx.win, 17, 0, on_close, &game);
	mlx_loop_hook(game.mlx.mlx, render_frame, &game);
	mlx_loop(game.mlx.mlx);
	mlx_destroy(&game);
	free_cub(&game.cub);
	return (0);
}
