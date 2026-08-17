/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:50:25 by yzoullik          #+#    #+#             */
/*   Updated: 2025/02/27 14:20:01 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	size_t	s1len;

	s1len = ft_strlen(s1);
	ptr = malloc(sizeof(char) * (s1len + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1len + 1);
	return (ptr);
}

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	srclen;

	srclen = ft_strlen(src);
	if (!dst && !dstsize)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	ft_strlcpy(&dst[dstlen], src, dstsize - dstlen);
	return (dstlen + srclen);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	char	*ptr;
	size_t	s1len;
	size_t	ptrlen;

	if (!s1 && !s2)
		return (0);
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s1len = ft_strlen(s1);
	ptrlen = s1len + ft_strlen(s2) + 1;
	ptr = malloc(sizeof(char) * ptrlen);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, s1len + 1);
	ft_strlcat(&ptr[s1len], s2, ptrlen);
	return (ptr);
}
