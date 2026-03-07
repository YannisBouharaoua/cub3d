/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 02:45:00 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 02:45:00 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	free_map_grid(t_map *map)
{
	int	i;

	if (!map || !map->grid)
		return ;
	i = 0;
	while (map->grid[i])
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
	map->grid = NULL;
	map->height = 0;
	map->width = 0;
}

void	free_cub(t_cub *cub)
{
	if (!cub)
		return ;
	free(cub->tex.north);
	free(cub->tex.south);
	free(cub->tex.west);
	free(cub->tex.east);
	cub->tex.north = NULL;
	cub->tex.south = NULL;
	cub->tex.west = NULL;
	cub->tex.east = NULL;
	free_map_grid(&cub->map);
}
