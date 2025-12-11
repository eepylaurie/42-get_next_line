/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatthes <lmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:36:30 by lmatthes          #+#    #+#             */
/*   Updated: 2025/12/11 18:57:29 by lmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

static char	*gnl_strjoin_copy(char *remainder, char *buffer, char *joined)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (remainder[i])
	{
		joined[i] = remainder[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		joined[i + j] = buffer[j];
		j++;
	}
	joined[i + j] = '\0';
	return (joined);
}

char	*gnl_strjoin(char *remainder, char *buffer)
{
	char	*joined;

	if (!buffer)
		return (free(remainder), NULL);
	if (!remainder)
	{
		remainder = malloc(1);
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
	}
	joined = malloc(gnl_strlen(remainder) + gnl_strlen(buffer) + 1);
	if (!joined)
		return (free(remainder), NULL);
	joined = gnl_strjoin_copy(remainder, buffer, joined);
	free(remainder);
	return (joined);
}
