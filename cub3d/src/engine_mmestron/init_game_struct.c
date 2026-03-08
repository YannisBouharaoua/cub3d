/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:10:00 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/08 00:10:00 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
