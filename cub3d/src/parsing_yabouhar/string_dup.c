/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_dup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:58:37 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:58:37 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*str_ndup(const char *s, size_t len)
{
	char	*dup;
	size_t	i;

	dup = (char *)malloc(sizeof(char) * (len + 1));
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

char	*str_dup(const char *s)
{
	if (!s)
		return (NULL);
	return (str_ndup(s, str_len(s)));
}
