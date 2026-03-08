/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_get.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	map_get(t_map *m, int mx, int my)
{
	if (!m || !m->grid)
		return (' ');
	if (my < 0 || my >= m->height || mx < 0)
		return (' ');
	if (!m->grid[my])
		return (' ');
	if (mx >= (int)str_len(m->grid[my]))
		return (' ');
	return (m->grid[my][mx]);
}

int	map_is_wall(t_map *m, int mx, int my)
{
	char	c;

	c = map_get(m, mx, my);
	if (c == ' ' || c == '1')
		return (1);
	return (0);
}
