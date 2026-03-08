/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:34:24 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:34:24 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	find_player(t_map *map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_player(map->grid[y][x]))
			{
				map->player_dir = map->grid[y][x];
				map->player_x = x;
				map->player_y = y;
				count++;
			}
			x++;
		}
		y++;
	}
	return (count == 1);
}
