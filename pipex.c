/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:21:58 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/11 13:10:17 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		(error(0), free(ptr1), ft_free(ptr), \
		close(list->stdin), free(list), exit(1));
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

int	main(int ac, char **av, char **env)
{
	t_list	*list;

	if (ac != 5)
		return (write(2, "ac != 5\n", 9), 1);
	list = ft_init(ac, av, env);
	if (pipe(list->fd) == -1)
	{
		if (list->in != -1)
			close(list->in);
		if (list->out != -1)
			close(list->out);
		(error(4), close(list->stdin), free(list), exit(1));
	}
	first_proc(list);
	(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
	last_proc(list);
	dup2(list->stdin, 0);
	close(list->stdin);
	close(list->out);
	return (ft_wait(list, 0));
}
