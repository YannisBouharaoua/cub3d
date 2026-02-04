/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabouhar <yabouhar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 16:40:00 by yabouhar          #+#    #+#             */
/*   Updated: 2026/02/04 16:40:00 by yabouhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdlib.h>

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

static int	has_cub_ext(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = str_len(s);
	if (len < 4)
		return (0);
	return (s[len - 4] == '.' && s[len - 3] == 'c'
		&& s[len - 2] == 'u' && s[len - 1] == 'b');
}

static int	starts_with(const char *s, const char *p)
{
	size_t	i;

	i = 0;
	while (p[i])
	{
		if (s[i] != p[i])
			return (0);
		i++;
	}
	return (1);
}

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

static int	is_map_line(char *line)
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
		if (!is_map_char(line[i]))
			return (0);
		i++;
	}
	return (0);
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

static int	is_only_spaces(char *line)
{
	size_t	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static int	is_config_line(char *line)
{
	char	*s;

	if (!line)
		return (0);
	s = line;
	while (*s == ' ')
		s++;
	if (*s == '\0' || *s == '\n' || *s == '\r')
		return (1);
	if (starts_with(s, "NO ") || starts_with(s, "SO ")
		|| starts_with(s, "WE ") || starts_with(s, "EA ")
		|| starts_with(s, "F ") || starts_with(s, "C "))
		return (1);
	return (0);
}

static void	free_lines(char **lines, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}

static int	push_line(char ***lines, int *count, int *cap, char *line)
{
	char	**tmp;
	int		i;

	if (*count + 1 > *cap)
	{
		*cap = (*cap == 0) ? 8 : (*cap * 2);
		tmp = (char **)malloc(sizeof(char *) * (*cap));
		if (!tmp)
			return (0);
		if (*lines)
		{
			i = 0;
			while (i < *count)
			{
				tmp[i] = (*lines)[i];
				i++;
			}
			free(*lines);
		}
		*lines = tmp;
	}
	(*lines)[*count] = str_dup(line);
	if (!(*lines)[*count])
		return (0);
	(*count)++;
	return (1);
}

static int	is_closed(char **lines, int height, int width)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			c = lines[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || x == 0 || y == height - 1 || x == width - 1)
					return (0);
				if (lines[y - 1][x] == ' ' || lines[y + 1][x] == ' '
					|| lines[y][x - 1] == ' ' || lines[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static char	**pad_lines(char **lines, int height, int width)
{
	char	**pad;
	int		y;
	int		x;

	pad = (char **)malloc(sizeof(char *) * height);
	if (!pad)
		return (NULL);
	y = 0;
	while (y < height)
	{
		pad[y] = (char *)malloc(width + 1);
		if (!pad[y])
		{
			free_lines(pad, y);
			return (NULL);
		}
		x = 0;
		while (x < width)
		{
			if (x < (int)str_len(lines[y]))
				pad[y][x] = lines[y][x];
			else
				pad[y][x] = ' ';
			x++;
		}
		pad[y][x] = '\0';
		y++;
	}
	return (pad);
}

int	good_map(char *path_map)
{
	int		fd;
	char	*line;
	int		in_map;
	int		end_map;
	int		player_count;
	int		width;
	int		height;
	int		cap;
	char	**lines;
	char	**pad;

	if (!path_map || !has_cub_ext(path_map))
		return (0);
	fd = open(path_map, O_RDONLY);
	if (fd == -1)
		return (0);
	in_map = 0;
	end_map = 0;
	player_count = 0;
	width = 0;
	height = 0;
	cap = 0;
	lines = NULL;
	while ((line = get_next_line(fd)))
	{
		if (!in_map && !is_map_line(line))
		{
			if (!is_config_line(line))
			{
				free(line);
				close(fd);
				return (0);
			}
			free(line);
			continue ;
		}
		in_map = 1;
		if (end_map)
		{
			if (!is_only_spaces(line))
			{
				free(line);
				close(fd);
				free_lines(lines, height);
				return (0);
			}
			free(line);
			continue ;
		}
		if (!is_map_line(line))
		{
			end_map = 1;
			free(line);
			continue ;
		}
		trim_eol(line);
		if (!push_line(&lines, &height, &cap, line))
		{
			free(line);
			close(fd);
			free_lines(lines, height);
			return (0);
		}
		if ((int)str_len(line) > width)
			width = (int)str_len(line);
		{
			int i = 0;
			while (line[i])
			{
				if (line[i] == 'N' || line[i] == 'S'
					|| line[i] == 'E' || line[i] == 'W')
					player_count++;
				if (!is_map_char(line[i]))
				{
					free(line);
					close(fd);
					free_lines(lines, height);
					return (0);
				}
				i++;
			}
		}
		free(line);
	}
	close(fd);
	if (!in_map || height == 0 || player_count != 1)
		return (0);
	pad = pad_lines(lines, height, width);
	if (!pad)
	{
		free_lines(lines, height);
		return (0);
	}
	if (!is_closed(pad, height, width))
	{
		free_lines(lines, height);
		free_lines(pad, height);
		return (0);
	}
	free_lines(lines, height);
	free_lines(pad, height);
	return (1);
}
