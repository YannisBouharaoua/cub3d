/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:53:12 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:53:12 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static char	*skip_spaces(char *s)
{
	while (*s == ' ')
		s++;
	return (s);
}

static int	parse_value(char **s, int *value)
{
	int	found;

	*s = skip_spaces(*s);
	found = 0;
	*value = 0;
	while (**s >= '0' && **s <= '9')
	{
		*value = *value * 10 + (**s - '0');
		(*s)++;
		found = 1;
	}
	return (found);
}

static int	parse_rgb(t_color *color, char *s)
{
	if (!parse_value(&s, &color->r) || color->r > 255)
		return (0);
	s = skip_spaces(s);
	if (*s++ != ',' || !parse_value(&s, &color->g) || color->g > 255)
		return (0);
	s = skip_spaces(s);
	if (*s++ != ',' || !parse_value(&s, &color->b) || color->b > 255)
		return (0);
	s = skip_spaces(s);
	return (*s == '\0' || *s == '\n' || *s == '\r');
}

int	gm_set_color(t_color *color, int *flag, char *s)
{
	if (*flag || !parse_rgb(color, s))
		return (0);
	*flag = 1;
	return (1);
}
