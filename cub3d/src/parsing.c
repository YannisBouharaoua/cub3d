/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <mmestron@student.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 14:07:03 by mmestron          #+#    #+#             */
/*   Updated: 2026/03/07 14:07:03 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	put_err(char *s)
{
	if (!s)
		return ;
	write(2, s, str_len(s));
}

int	not_directory(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY | O_DIRECTORY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	print_error(char *msg)
{
	put_err("Error\n");
	put_err(msg);
	put_err("\n");
	return (0);
}

char	*str_chr(const char *s, int c)
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
