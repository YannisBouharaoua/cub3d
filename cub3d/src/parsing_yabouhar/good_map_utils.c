/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:13:47 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:13:47 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	starts_with_id(char *s, char *id)
{
	if (s[0] != id[0] || s[1] != id[1])
		return (0);
	return (s[2] == ' ');
}

int	gm_has_cub_ext(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = str_len(s);
	if (len < 4)
		return (0);
	if (s[len - 4] != '.')
		return (0);
	if (s[len - 3] != 'c')
		return (0);
	if (s[len - 2] != 'u')
		return (0);
	if (s[len - 1] != 'b')
		return (0);
	return (1);
}

int	gm_is_config_line(char *line)
{
	char	*s;

	if (is_empty_line(line))
		return (1);
	s = line;
	while (*s == ' ')
		s++;
	if (starts_with_id(s, "NO") || starts_with_id(s, "SO"))
		return (1);
	if (starts_with_id(s, "WE") || starts_with_id(s, "EA"))
		return (1);
	if ((*s == 'F' || *s == 'C') && s[1] == ' ')
		return (1);
	return (0);
}

void	gm_free_lines(char **lines, int count)
{
	int	i;

	if (!lines)
		return ;
	i = 0;
	while (i < count)
	{
		free(lines[i]);
		i++;
	}
	free(lines);
}
