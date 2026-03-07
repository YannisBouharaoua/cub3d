/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:09:54 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:09:54 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	init_cub(t_cub *cub)
{
	if (!cub)
		return ;
	cub->tex.north = NULL;
	cub->tex.south = NULL;
	cub->tex.west = NULL;
	cub->tex.east = NULL;
	cub->floor.r = -1;
	cub->floor.g = -1;
	cub->floor.b = -1;
	cub->ceiling.r = -1;
	cub->ceiling.g = -1;
	cub->ceiling.b = -1;
	cub->map.grid = NULL;
	cub->map.width = 0;
	cub->map.height = 0;
	cub->map.player_dir = 0;
	cub->map.player_x = 0;
	cub->map.player_y = 0;
}

static void	init_images(t_game *game)
{
	game->mlx.mlx = NULL;
	game->mlx.win = NULL;
	game->mlx.w = 0;
	game->mlx.h = 0;
	game->mlx.frame.img = NULL;
	game->mlx.frame.addr = NULL;
	game->tex_no.img = NULL;
	game->tex_so.img = NULL;
	game->tex_we.img = NULL;
	game->tex_ea.img = NULL;
}

void	init_game_struct(t_game *game)
{
	int	i;

	if (!game)
		return ;
	init_cub(&game->cub);
	init_images(game);
	game->player.x = 0.0;
	game->player.y = 0.0;
	game->player.angle = 0.0;
	game->floor_color = 0;
	game->ceil_color = 0;
	i = 0;
	while (i < 1024)
	{
		game->keys[i] = 0;
		i++;
	}
}
