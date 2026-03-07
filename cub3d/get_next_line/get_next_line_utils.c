/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmestron <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:35:24 by mmestron          #+#    #+#             */
/*   Updated: 2024/12/02 14:35:26 by mmestron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*gnl_strchr(char *s, char c)
{
	while (s && *s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strdup(const char *s, int ln)
{
	char	*dup;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (ln)
		i++;
	dup = (char *)malloc((i + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	if (ln)
		dup[i++] = '\n';
	dup[i] = '\0';
	return (dup);
}

static char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	joined = (char *)malloc((i + j + 1) * sizeof(char));
	if (!joined)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		joined[i] = s1[i];
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = '\0';
	return (joined);
}

int	read_it(int fd, char **buffer, int *reader)
{
	char	*tmp;
	char	*temp;

	tmp = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!tmp)
		return (0);
	*reader = read(fd, tmp, BUFFER_SIZE);
	if (*reader <= 0)
	{
		free(tmp);
		return (*reader);
	}
	tmp[*reader] = '\0';
	if (*buffer == NULL)
		*buffer = gnl_strdup("", 0);
	temp = gnl_strjoin(*buffer, tmp);
	free(*buffer);
	*buffer = gnl_strdup(temp, 0);
	free(temp);
	free(tmp);
	return (*reader);
}

char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	char	*next_line_pos;

	next_line_pos = gnl_strchr(*buffer, '\n');
	if (next_line_pos)
	{
		if (*next_line_pos == '\n')
			*next_line_pos = '\0';
		line = gnl_strdup(*buffer, 1);
		temp = gnl_strdup(++next_line_pos, 0);
		free(*buffer);
		*buffer = temp;
	}
	else
	{
		line = gnl_strdup(*buffer, 0);
		free(*buffer);
		*buffer = NULL;
	}
	return (line);
}
