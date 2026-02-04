/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:35:16 by mmestron          #+#    #+#             */
/*   Updated: 2024/12/02 14:35:18 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static void	free_if_err(char **buffer, int *rd)
{
	if (*rd == -1)
	{
		free(*buffer);
		*buffer = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			reader;

	reader = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!gnl_strchr(buffer, '\n'))
	{
		if (read_it(fd, &buffer, &reader) <= 0)
			break ;
	}
	free_if_err(&buffer, &reader);
	if (buffer == NULL)
		return (NULL);
	if (*buffer == '\0')
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = extract_line(&buffer);
	return (line);
}
