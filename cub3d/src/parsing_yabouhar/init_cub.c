/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 00:10:00 by yabouhar          #+#    #+#             */
/*   Updated: 2026/03/08 00:10:00 by yabouhar         ###   ########.fr       */
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
