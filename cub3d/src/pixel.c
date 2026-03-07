/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:10:00 by coder             #+#    #+#             */
/*   Updated: 2026/02/04 17:10:00 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	put_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;
	int		bytes;

	if (!g || !g->mlx.frame.addr)
		return ;
	if (x < 0 || y < 0 || x >= g->mlx.w || y >= g->mlx.h)
		return ;
	bytes = g->mlx.frame.bpp / 8;
	dst = g->mlx.frame.addr + (y * g->mlx.frame.line_len + x * bytes);
	*(unsigned int *)dst = (unsigned int)color;
}
