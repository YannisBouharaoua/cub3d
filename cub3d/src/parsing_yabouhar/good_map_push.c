/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_map_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:15:12 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:15:12 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static int	gm_expand(char ***lines, int count, int *cap)
{
	char	**tmp;
	int		i;

	if (*cap == 0)
		*cap = 8;
	else
		*cap = *cap * 2;
	tmp = (char **)malloc(sizeof(char *) * (*cap + 1));
	if (!tmp)
		return (0);
	i = 0;
	while (*lines && i < count)
	{
		tmp[i] = (*lines)[i];
		i++;
	}
	tmp[i] = NULL;
	free(*lines);
	*lines = tmp;
	return (1);
}

int	gm_push_line(char ***lines, int *count, int *cap, char *line)
{
	if (*count >= *cap && !gm_expand(lines, *count, cap))
		return (0);
	(*lines)[*count] = str_dup(line);
	if (!(*lines)[*count])
		return (0);
	(*count)++;
	(*lines)[*count] = NULL;
	return (1);
}
