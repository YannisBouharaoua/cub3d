/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:39:49 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:39:49 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	good_map(char *path_map)
{
	t_cub	cub;

	if (!parse_cub(&cub, path_map))
		return (0);
	free_cub(&cub);
	return (1);
}
