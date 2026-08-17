/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:42:57 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/08 11:18:38 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **ptr)
{
	size_t	i;

	i = 0;
	if (ptr && ptr[i])
		while (ptr[i])
			free(ptr[i++]);
	if (ptr)
	{
		free(ptr);
		ptr = 0;
	}
}

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	haylen;

	if (!haystack && needle && !len)
		return (0);
	i = 0;
	if (needle[i] == '\0')
		return ((char *) haystack);
	haylen = ft_strlen(haystack);
	if (len > haylen)
		len = haylen;
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len)
			j++;
		if (needle[j] == '\0')
			return ((char *) &haystack[i]);
		i++;
	}
	return (0);
}

char	*ft_strrchr(char *s, int c)
{
	size_t	slen;

	slen = ft_strlen(s);
	while ((int) slen >= 0)
	{
		if (s[slen] == (char) c)
			return ((char *) &s[slen + 1]);
		slen--;
	}
	return ((char *) &s[slen + 1]);
}

void	error(int i)
{
	if (i == 0)
		write(2, "Command not found\n", 19);
	if (i == 1)
		write(2, "Error in fork\n", 15);
	if (i == 2)
		write(2, "No such file or directory\n", 27);
	if (i == 3)
		write(2, "Permission denied\n", 19);
	if (i == 4)
		write(2, "Error in pipe\n", 15);
	if (i == 5)
		write(2, "Error in list struct\n", 22);
}
