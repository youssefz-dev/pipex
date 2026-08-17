/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 12:32:48 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/08 16:16:26 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_ischar(char i, char c)
{
	if (i == c)
		return (1);
	return (0);
}

size_t	ft_strcount(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_ischar(s[i], c) && (ft_ischar(s[i + 1], c) || s[i + 1] == '\0'))
			j++;
		i++;
	}
	return (j);
}

size_t	ft_chrcount(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (!ft_ischar(s[i], c))
			j++;
		if (!ft_ischar(s[i], c) && (ft_ischar(s[i + 1], c) || s[i + 1] == '\0'))
			return (j);
		i++;
	}
	return (j);
}

int	ft_solve(char const *s, char *str, char **ptr, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (j == 0 && !ft_ischar(s[i], c))
		{
			str = malloc(sizeof(char) * (ft_chrcount(&s[i], c) + 1));
			if (!str)
				return (0);
		}
		if (!ft_ischar(s[i], c))
			str[j++] = s[i];
		if (!ft_ischar(s[i], c) && (ft_ischar(s[i + 1], c) || s[i + 1] == '\0'))
		{
			str[j] = '\0';
			*ptr++ = str;
			j = 0;
		}
		i++;
	}
	*ptr = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	char	*str;

	if (!s)
		return (0);
	ptr = malloc(sizeof(char *) * (ft_strcount(s, c) + 1));
	if (!ptr)
		return (0);
	str = 0;
	if (!ft_solve(s, str, ptr, c))
		return (ft_free(ptr), free(str), str = 0, ptr);
	return (ptr);
}
