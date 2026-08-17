/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 12:42:57 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/08 11:50:58 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

int	ft_wait(t_list *list, int i)
{
	int	status;
	int	statuscode;
	int	id;

	statuscode = 0;
	id = wait(&status);
	while (id != -1)
	{
		if (id == list->pid)
			if (WIFEXITED(status))
				statuscode = WEXITSTATUS(status);
		id = wait(&status);
	}
	if (i == 1)
		return (free(list), 1);
	return (free(list), statuscode);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (!s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}
