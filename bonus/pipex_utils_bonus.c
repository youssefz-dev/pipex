/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:13:37 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/12 11:19:03 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_list	*ft_init(int ac, char **av, char **env)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		(error(5), exit(1));
	list->ac = ac;
	list->av = av;
	list->env = env;
	list->in = open(av[1], O_RDONLY);
	list->out = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	list->stdin = dup(0);
	list->pid = 0;
	return (list);
}

void	first_proc(t_list *list, char *av)
{
	if (pipe(list->fd) == -1)
	{
		if (list->in != -1)
			close(list->in);
		if (list->out != -1)
			close(list->out);
		(error(4), close(list->stdin), free(list), exit(1));
	}
	if (list->in != -1)
	{
		(dup2(list->in, 0), close(list->in));
		list->pid = fork();
		if (list->pid == -1)
			(close(list->fd[0]), close(list->fd[1]), close(list->out), \
			error(1), close(list->stdin), free(list), exit(1));
		if (list->pid == 0)
		{
			if (list->out != -1)
				close(list->out);
			(close(list->fd[0]), pipex(av, list, list->fd[1]));
		}
	}
	else
		error(2);
}

void	last_proc(t_list *list, char *av)
{
	if (list->out != -1)
	{
		list->pid = fork();
		if (list->pid == -1)
			(close(list->out), error(1), close(list->stdin), \
			free(list), exit(1));
		if (list->pid == 0)
			(pipex(av, list, list->out));
	}
	else
	{
		error(3);
		dup2(list->stdin, 0);
		close(list->stdin);
		exit(ft_wait(list, 1));
	}
}
