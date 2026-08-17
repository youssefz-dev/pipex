/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:58 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/12 12:46:50 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*path_finder(char **path, char *cmd)
{
	char	*res1;
	char	*res2;
	int		i;

	i = 0;
	while (path[i++])
	{
		res1 = ft_strjoin1(path[i], "/");
		if (!res1)
			return (ft_free(path), NULL);
		res2 = ft_strjoin1(res1, cmd);
		if (!res2)
			return (ft_free(path), free(res1), NULL);
		if (access(res2, X_OK) != -1)
			return (ft_free(path), free(res1), res2);
		(free(res1), free(res2));
	}
	return (ft_free(path), NULL);
}

char	*get_path(char *cmd, char **env)
{
	char	**path;
	int		i;

	i = 0;
	while (env[i++])
		if (ft_strnstr(env[i], "PATH=", 5))
			break ;
	path = ft_split(&env[i][5], ':');
	if (!path)
		return (NULL);
	return (path_finder(path, cmd));
}

void	pipex(char *av, t_list *list, int fd)
{
	char	**ptr;
	char	*ptr1;

	dup2(fd, 1);
	close(fd);
	ptr = ft_split(av, ' ');
	if (!ptr || !*ptr)
		(error(0), free(ptr), close(list->stdin), free(list), exit(1));
	if (access(ptr[0], X_OK) != -1)
		if (execve(ptr[0], ptr, list->env) == -1)
			(error(0), ft_free(ptr), close(list->stdin), free(list), exit(1));
	if (ptr[0][0] == '.' || ptr[0][0] == '/')
		(error(0), ft_free(ptr), close(list->stdin), free(list), exit(1));
	ptr1 = get_path(ptr[0], list->env);
	if (!ptr1)
		(error(0), ft_free(ptr), close(list->stdin), free(list), exit(1));
	if (execve(ptr1, ptr, list->env) == -1)
		(error(0), free(ptr1), ft_free(ptr), close(list->stdin), \
		free(list), exit(1));
}

void	fpipe(t_list *list, int i)
{
	while (++i < list->ac - 2)
	{
		if (pipe(list->fd) == -1)
			(close(list->fd[0]), close(list->fd[1]), close(list->out), \
			error(4), close(list->stdin), free(list), exit(1));
		list->pid = fork();
		if (list->pid == -1)
			(close(list->fd[0]), close(list->fd[1]), close(list->out), \
			error(1), close(list->stdin), free(list), exit(1));
		if (list->pid == 0)
		{
			if (list->out != -1)
				close(list->out);
			(close(list->fd[0]), pipex(list->av[i], list, list->fd[1]));
		}
		(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
	}
}

int	main(int ac, char **av, char **env)
{
	t_list	*list;

	if (ac < 5)
		return (write(2, "ac < 5\n", 8), 1);
	if (ft_strnstr(av[1], "here_doc", 9) && ft_strlen(av[1]) == 8)
		return (here_doc(ac, av, env));
	list = ft_init(ac, av, env);
	first_proc(list, av[2]);
	(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
	fpipe(list, 2);
	last_proc(list, av[ac - 2]);
	dup2(list->stdin, 0);
	close(list->stdin);
	close(list->out);
	return (ft_wait(list, 0));
}
