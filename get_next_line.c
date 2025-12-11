/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatthes <lmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 21:41:35 by lmatthes          #+#    #+#             */
/*   Updated: 2025/12/11 18:46:00 by lmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*fill_remainder(int fd, char *remainder)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(remainder), NULL);
	read_bytes = 1;
	while (!gnl_strchr(remainder, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), free(remainder), NULL);
		buffer[read_bytes] = '\0';
		remainder = gnl_strjoin(remainder, buffer);
		if (!remainder)
			return (free(buffer), NULL);
	}
	free(buffer);
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	size_t	i;

	if (!remainder || !remainder[0])
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	line = malloc(i + (remainder[i] == '\n') + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
	{
		line[i] = remainder[i];
		i++;
	}
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*trim_remainder(char *remainder)
{
	char	*new_remainder;
	size_t	i;
	size_t	j;

	if (!remainder)
		return (NULL);
	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
		return (free(remainder), NULL);
	new_remainder = malloc(gnl_strlen(remainder) - i + 1);
	if (!new_remainder)
		return (free(remainder), NULL);
	i++;
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = fill_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	if (!line)
		return (free(remainder), remainder = NULL, NULL);
	remainder = trim_remainder(remainder);
	return (line);
}
