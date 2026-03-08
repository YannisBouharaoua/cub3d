/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:30:13 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:30:13 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	trim_eol(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
		i++;
	line[i] = '\0';
}

static int	has_all_config(t_gm *gm)
{
	return (gm->no && gm->so && gm->we && gm->ea && gm->f && gm->c);
}

static int	store_map_line(t_gm *gm)
{
	size_t	len;

	if (!gm_push_line(&gm->lines, &gm->height, &gm->cap, gm->line))
		return (0);
	len = str_len(gm->line);
	if ((int)len > gm->width)
		gm->width = (int)len;
	return (1);
}

static int	read_line(t_gm *gm)
{
	trim_eol(gm->line);
	if (!gm->in_map && is_empty_line(gm->line))
		return (1);
	if (!gm->in_map && is_map_line(gm->line))
	{
		if (!has_all_config(gm))
			return (0);
		gm->in_map = 1;
	}
	if (gm->in_map)
	{
		if (!is_map_line(gm->line))
			return (0);
		return (store_map_line(gm));
	}
	return (gm_is_config_line(gm->line) && gm_parse_config(gm->line, gm));
}

int	read_cub_file(t_gm *gm)
{
	gm->line = get_next_line(gm->fd);
	while (gm->line)
	{
		if (!read_line(gm))
		{
			free(gm->line);
			gm->line = NULL;
			gnl_clear();
			return (0);
		}
		free(gm->line);
		gm->line = get_next_line(gm->fd);
	}
	gnl_clear();
	return (1);
}
