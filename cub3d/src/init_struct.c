/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 15:10:21 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 15:10:21 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

int	is_map_line(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (is_map_char(line[i]) && line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int	count_map_height(int fd)
{
	char	*line;
	int		height;
	int		in_map;

	height = 0;
	in_map = 0;
	while ((line = get_next_line(fd)))
	{
		if (!in_map && is_map_line(line))
			in_map = 1;
		if (in_map)
		{
			if (!is_map_line(line))
			{
				free(line);
				break ;
			}
			height++;
		}
		free(line);
	}
	return (height);
}

void	alloc_map(t_map *map, int height)
{
	map->grid = malloc(sizeof(char *) * (height + 1));
	map->height = height;
	map->width = 0;
}

static char	*trim_eol(char *line)
{
	size_t	len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		len--;
	line[len] = '\0';
	return (line);
}

void	fill_map(t_map *map, int fd)
{
	char	*line;
	int		i;
	int		in_map;

	i = 0;
	in_map = 0;
	while ((line = get_next_line(fd)))
	{
		if (!in_map && is_map_line(line))
			in_map = 1;
		if (in_map)
		{
			if (!is_map_line(line))
			{
				free(line);
				break ;
			}
			line = trim_eol(line);
			map->grid[i] = ft_strdup(line);
			if ((int)ft_strlen(map->grid[i]) > map->width)
				map->width = ft_strlen(map->grid[i]);
			i++;
		}
		free(line);
	}
	map->grid[i] = NULL;
}

void	find_player(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (ft_strchr("NSEW", map->grid[y][x]))
			{
				map->player_dir = map->grid[y][x];
				map->player_x = x;
				map->player_y = y;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_map(t_map *map, char *path_map)
{
	int	fd;
	int	height;

	fd = open(path_map, O_RDONLY);
	height = count_map_height(fd);
	close(fd);
	alloc_map(map, height);
	fd = open(path_map, O_RDONLY);
	fill_map(map, fd);
	close(fd);
	find_player(map);
}
