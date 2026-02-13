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
#include <stdlib.h>

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

int	is_map_line(char *line)
{
	int	i;
	int	has_map_token;

	if (!line)
		return (0);
	i = 0;
	has_map_token = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_map_token = 1;
		i++;
	}
	return (has_map_token);
}

static size_t	str_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*str_dup(const char *s)
{
	char	*dup;
	size_t	i;
	size_t	len;

	if (!s)
		return (NULL);
	len = str_len(s);
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static char	*str_chr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
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
	len = str_len(line);
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
			map->grid[i] = str_dup(line);
			if ((int)str_len(map->grid[i]) > map->width)
				map->width = str_len(map->grid[i]);
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
			if (str_chr("NSEW", map->grid[y][x]))
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

	if (!map || !path_map)
		return ;
	fd = open(path_map, O_RDONLY);
	if (fd < 0)
	{
		map->grid = NULL;
		map->height = 0;
		map->width = 0;
		map->player_dir = 0;
		map->player_x = 0;
		map->player_y = 0;
		return ;
	}
	height = count_map_height(fd);
	close(fd);
	alloc_map(map, height);
	fd = open(path_map, O_RDONLY);
	if (fd < 0)
	{
		free(map->grid);
		map->grid = NULL;
		map->height = 0;
		map->width = 0;
		map->player_dir = 0;
		map->player_x = 0;
		map->player_y = 0;
		return ;
	}
	fill_map(map, fd);
	close(fd);
	find_player(map);
}
