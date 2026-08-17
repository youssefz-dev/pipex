/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:11:42 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/08 11:38:40 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	ft_intlen(long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (++i);
	if (nbr < 0)
		nbr *= -(++i);
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		ptrlen;
	long	nbr;

	nbr = n;
	ptrlen = ft_intlen(nbr);
	ptr = malloc(sizeof(char) * (ptrlen + 1));
	if (!ptr)
		return (0);
	if (nbr < 0)
		nbr *= -1;
	ptr[ptrlen--] = '\0';
	while (ptrlen >= 0)
	{
		ptr[ptrlen--] = (nbr % 10) + 48;
		nbr /= 10;
	}
	if (n < 0)
		ptr[0] = '-';
	return (ptr);
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

void	files_error(int in, int out)
{
	int	i;

	i = 0;
	if (in == -1 || out == -1)
	{
		if (in == -1)
			error(2);
		if (out == -1)
		{
			error(3);
			i = 1;
		}
		if (in != -1)
			close(in);
		if (out != -1)
			close(out);
		exit(i);
	}
}

void	files_error1(int in, int out, int pipe, int *fd)
{
	int	i;

	i = 0;
	if (in == -1 || out == -1 || pipe == -1)
	{
		if (in == -1)
			error(2);
		if (out == -1)
		{
			error(3);
			i = 1;
		}
		if (pipe == -1)
		{
			error(4);
			i = 1;
		}
		if (in != -1)
			close(in);
		if (out != -1)
			close(out);
		if (pipe != -1)
			(close(fd[0]), close(fd[1]));
		exit(i);
	}
}
