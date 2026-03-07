/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:25:10 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:25:10 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	cell_is_closed(char **grid, int y, int x)
{
	if (grid[y][x] != '0' && grid[y][x] != 'N'
		&& grid[y][x] != 'S' && grid[y][x] != 'E'
		&& grid[y][x] != 'W')
		return (1);
	if (grid[y - 1][x] == ' ' || grid[y + 1][x] == ' ')
		return (0);
	if (grid[y][x - 1] == ' ' || grid[y][x + 1] == ' ')
		return (0);
	return (1);
}

int	gm_is_closed(char **lines, int height, int width)
{
	int	y;
	int	x;

	y = 1;
	while (y <= height)
	{
		x = 1;
		while (x <= width)
		{
			if (!cell_is_closed(lines, y, x))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

static int	fill_row(char *row, int width)
{
	int	x;

	x = 0;
	while (x < width + 2)
		row[x++] = ' ';
	row[x] = '\0';
	return (1);
}

static char	**alloc_pad(int height, int width)
{
	char	**pad;
	int		y;

	pad = (char **)malloc(sizeof(char *) * (height + 3));
	if (!pad)
		return (NULL);
	y = 0;
	while (y < height + 2)
	{
		pad[y] = (char *)malloc(sizeof(char) * (width + 3));
		if (!pad[y])
			return (gm_free_lines(pad, y), NULL);
		fill_row(pad[y], width);
		y++;
	}
	pad[y] = NULL;
	return (pad);
}

char	**gm_pad_lines(char **lines, int height, int width)
{
	char	**pad;
	int		x;
	int		y;

	pad = alloc_pad(height, width);
	if (!pad)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (lines[y][x])
		{
			pad[y + 1][x + 1] = lines[y][x];
			x++;
		}
		y++;
	}
	return (pad);
}
