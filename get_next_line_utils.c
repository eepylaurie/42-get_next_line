/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmatthes <lmatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 22:36:30 by lmatthes          #+#    #+#             */
/*   Updated: 2025/12/05 19:01:35 by lmatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr_gnl(const char *s, int c)
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

// char	*ft_strjoin_gnl(char *s1, char *s2)
// {
// 	char	*new;
// 	size_t	i;
// 	size_t	j;

// 	if (!s1)
// 	{
// 		s1 = malloc(1);
// 		if (!s1)
// 			return (NULL);
// 		s1[0] = '\0';
// 	}
// 	new = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
// 	if (!new)
// 		return (free(s1), NULL);
// 	i = 0;
// 	while (s1[i])
// 	{
// 		new[i] = s1[i];
// 		i++;
// 	}
// 	j = 0;
// 	while (s2[j])
// 		new[i++] = s2[j++];
// 	new[i] = '\0';
// 	return (free(s1), new);
// }

static char	*ft_strjoin_core(char *s1, char *s2, char *new)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*new;

	if (!s2)
		return (free(s1), NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	new = malloc(ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1);
	if (!new)
		return (free(s1), NULL);
	new = ft_strjoin_core(s1, s2, new);
	free(s1);
	return (new);
}

