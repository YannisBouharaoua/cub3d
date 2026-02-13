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
	int	has_token;

	if (!line)
		return (0);
	i = 0;
	has_token = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i] == '\r')
			break ;
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_token = 1;
		i++;
	}
	return (has_token);
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

static void	trim_trailing_ws(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = str_len(s);
	while (len > 0)
	{
		if (s[len - 1] == ' ' || s[len - 1] == '\n'
			|| s[len - 1] == '\r' || s[len - 1] == '\t')
			len--;
		else
			break ;
	}
	s[len] = '\0';
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

static char	*skip_spaces(char *s)
{
	while (s && *s == ' ')
		s++;
	return (s);
}

static int	is_only_spaces_str(const char *s)
{
	while (s && *s)
	{
		if (*s != ' ')
			return (0);
		s++;
	}
	return (1);
}

static int	parse_int_range(const char **s, int *out, int min, int max)
{
	long	val;
	int		digits;

	val = 0;
	digits = 0;
	while (**s == ' ')
		(*s)++;
	while (**s >= '0' && **s <= '9')
	{
		val = val * 10 + (**s - '0');
		if (val > max)
			return (0);
		(*s)++;
		digits++;
	}
	if (digits == 0 || val < min || val > max)
		return (0);
	*out = (int)val;
	return (1);
}

static int	parse_rgb(char *s)
{
	int		r;
	int		g;
	int		b;
	const char	*p;

	trim_trailing_ws(s);
	p = s;
	if (!parse_int_range(&p, &r, 0, 255))
		return (0);
	while (*p == ' ')
		p++;
	if (*p != ',')
		return (0);
	p++;
	if (!parse_int_range(&p, &g, 0, 255))
		return (0);
	while (*p == ' ')
		p++;
	if (*p != ',')
		return (0);
	p++;
	if (!parse_int_range(&p, &b, 0, 255))
		return (0);
	while (*p == ' ' || *p == '\n' || *p == '\r' || *p == '\t')
		p++;
	if (*p != '\0')
		return (0);
	return (1);
}

static int	check_path_token(char *s)
{
	int		fd;
	int		dfd;
	char	*end;

	if (!s || *s == '\0')
		return (0);
	trim_trailing_ws(s);
	end = s + str_len(s);
	while (end > s && *(end - 1) == ' ')
		end--;
	*end = '\0';
	if (*s == '\0')
		return (0);
	if (!is_only_spaces_str(s) && str_chr(s, ' '))
		return (0);
	fd = open(s, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	dfd = open(s, O_RDONLY | O_DIRECTORY);
	if (dfd != -1)
	{
		close(dfd);
		return (0);
	}
	return (1);
}

static int	parse_config(char *line, int *no, int *so, int *we, int *ea,
		int *f, int *c)
{
	char	*s;

	s = skip_spaces(line);
	if (!s || *s == '\0' || *s == '\n' || *s == '\r')
		return (1);
	if (starts_with(s, "NO "))
		return (!(*no) && ((*no = 1), check_path_token(skip_spaces(s + 2))));
	if (starts_with(s, "SO "))
		return (!(*so) && ((*so = 1), check_path_token(skip_spaces(s + 2))));
	if (starts_with(s, "WE "))
		return (!(*we) && ((*we = 1), check_path_token(skip_spaces(s + 2))));
	if (starts_with(s, "EA "))
		return (!(*ea) && ((*ea = 1), check_path_token(skip_spaces(s + 2))));
	if (starts_with(s, "F "))
		return (!(*f) && ((*f = 1), parse_rgb(skip_spaces(s + 1))));
	if (starts_with(s, "C "))
		return (!(*c) && ((*c = 1), parse_rgb(skip_spaces(s + 1))));
	return (0);
}

static void	flood_spaces(char **g, int h, int w, int y, int x)
{
	if (y < 0 || x < 0 || y >= h || x >= w)
		return ;
	if (g[y][x] != ' ')
		return ;
	g[y][x] = 'X';
	flood_spaces(g, h, w, y - 1, x);
	flood_spaces(g, h, w, y + 1, x);
	flood_spaces(g, h, w, y, x - 1);
	flood_spaces(g, h, w, y, x + 1);
}

static int	is_closed(char **lines, int height, int width)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < height)
	{
		if (lines[y][0] == ' ')
			flood_spaces(lines, height, width, y, 0);
		if (lines[y][width - 1] == ' ')
			flood_spaces(lines, height, width, y, width - 1);
		y++;
	}
	x = 0;
	while (x < width)
	{
		if (lines[0][x] == ' ')
			flood_spaces(lines, height, width, 0, x);
		if (lines[height - 1][x] == ' ')
			flood_spaces(lines, height, width, height - 1, x);
		x++;
	}
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
				if (lines[y - 1][x] == 'X' || lines[y + 1][x] == 'X'
					|| lines[y][x - 1] == 'X' || lines[y][x + 1] == 'X')
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
	int		player_count;
	int		width;
	int		height;
	int		cap;
	char	**lines;
	char	**pad;
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;

	if (!path_map || !has_cub_ext(path_map))
		return (0);
	fd = open(path_map, O_RDONLY);
	if (fd == -1)
		return (0);
	in_map = 0;
	player_count = 0;
	width = 0;
	height = 0;
	cap = 0;
	lines = NULL;
	no = 0;
	so = 0;
	we = 0;
	ea = 0;
	f = 0;
	c = 0;
	while ((line = get_next_line(fd)))
	{
		if (!in_map && !is_map_line(line))
		{
			if (!is_config_line(line) || !parse_config(line,
					&no, &so, &we, &ea, &f, &c))
			{
				free(line);
				close(fd);
				return (0);
			}
			free(line);
			continue ;
		}
		in_map = 1;
		if (!(no && so && we && ea && f && c))
		{
			free(line);
			close(fd);
			return (0);
		}
		if (!is_map_line(line))
		{
			free(line);
			close(fd);
			free_lines(lines, height);
			return (0);
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
