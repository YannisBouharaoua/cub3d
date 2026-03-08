/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:11:59 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:11:59 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	is_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

int	is_empty_line(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] == ' ')
		i++;
	return (line[i] == '\0' || line[i] == '\n' || line[i] == '\r');
}

int	is_map_line(char *line)
{
	int	i;
	int	has_char;

	if (!line)
		return (0);
	i = 0;
	has_char = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\r')
	{
		if (!is_map_char(line[i]))
			return (0);
		if (line[i] != ' ')
			has_char = 1;
		i++;
	}
	return (has_char);
}

size_t	str_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
