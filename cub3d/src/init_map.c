/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:32:49 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:32:49 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	assign_map(t_gm *gm)
{
	gm->cub->map.grid = gm->lines;
	gm->cub->map.height = gm->height;
	gm->cub->map.width = gm->width;
	gm->lines = NULL;
	gm->height = 0;
	gm->cap = 0;
}

int	build_map(t_gm *gm)
{
	if (!gm->in_map || gm->height == 0)
		return (0);
	gm->pad = gm_pad_lines(gm->lines, gm->height, gm->width);
	if (!gm->pad)
		return (0);
	if (!gm_is_closed(gm->pad, gm->height, gm->width))
	{
		gm_free_lines(gm->pad, gm->height + 2);
		gm->pad = NULL;
		return (0);
	}
	gm_free_lines(gm->pad, gm->height + 2);
	gm->pad = NULL;
	assign_map(gm);
	if (!find_player(&gm->cub->map))
	{
		free_map_grid(&gm->cub->map);
		return (0);
	}
	return (1);
}
