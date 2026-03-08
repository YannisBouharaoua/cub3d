/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_cfg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:21:35 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:21:35 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	*skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

static char	*trim_token(char *s)
{
	size_t	len;

	s = skip_spaces(s);
	len = str_len(s);
	while (len > 0 && (s[len - 1] == ' ' || s[len - 1] == '\n'
			|| s[len - 1] == '\r'))
		len--;
	return (str_ndup(s, len));
}

static int	check_path(char *path)
{
	int	fd;
	int	dfd;

	if (!path || *path == '\0')
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	dfd = open(path, O_RDONLY | O_DIRECTORY);
	if (dfd != -1)
		return (close(dfd), 0);
	return (1);
}

static int	set_texture(char **dst, int *flag, char *s)
{
	char	*path;

	path = trim_token(s);
	if (*flag || !path || !check_path(path))
	{
		free(path);
		return (0);
	}
	*flag = 1;
	*dst = path;
	return (1);
}

int	gm_parse_config(char *line, t_gm *gm)
{
	char	*s;

	s = skip_spaces(line);
	if (is_empty_line(s))
		return (1);
	if (s[0] == 'N' && s[1] == 'O' && s[2] == ' ')
		return (set_texture(&gm->cub->tex.north, &gm->no, s + 3));
	if (s[0] == 'S' && s[1] == 'O' && s[2] == ' ')
		return (set_texture(&gm->cub->tex.south, &gm->so, s + 3));
	if (s[0] == 'W' && s[1] == 'E' && s[2] == ' ')
		return (set_texture(&gm->cub->tex.west, &gm->we, s + 3));
	if (s[0] == 'E' && s[1] == 'A' && s[2] == ' ')
		return (set_texture(&gm->cub->tex.east, &gm->ea, s + 3));
	if (s[0] == 'F' && s[1] == ' ')
		return (gm_set_color(&gm->cub->floor, &gm->f, s + 2));
	if (s[0] == 'C' && s[1] == ' ')
		return (gm_set_color(&gm->cub->ceiling, &gm->c, s + 2));
	return (0);
}
