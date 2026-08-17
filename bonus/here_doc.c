/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 10:49:12 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/12 12:46:39 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*new_file(void)
{
	unsigned long	i;
	char			*ptr;
	char			*path;

	i = 0;
	ptr = ft_itoa(i);
	if (!ptr)
		return (0);
	path = ft_strjoin1("./", ptr);
	if (!path)
		return (free(ptr), NULL);
	free(ptr);
	while (access(path, F_OK) == 0)
	{
		if (i == 4294967295)
			return (NULL);
		ptr = ft_itoa(i++);
		if (!ptr)
			return (free(path), NULL);
		path = ft_strjoin1("./", ptr);
		if (!path)
			return (free(ptr), NULL);
		free(ptr);
	}
	return (path);
}

int	open_file(char *ptr, char *ptr1)
{
	int		in;

	free(ptr);
	ptr = new_file();
	if (!ptr)
		return (free(ptr1), -1);
	in = open(ptr, O_CREAT | O_RDWR);
	if (in == -1)
		return (free(ptr), free(ptr1), in);
	ft_putstr_fd(ptr1, in);
	close(in);
	in = open(ptr, O_CREAT | O_RDWR);
	return (unlink(ptr), free(ptr), free(ptr1), in);
}

int	create_file(char **av)
{
	char	*ptr;
	char	*ptr1;

	ptr1 = 0;
	ptr = get_next_line(0);
	if (!ptr)
		return (-1);
	if (ft_strnstr(ptr, av[2], ft_strlen(av[2])) && \
	ft_strlen(ptr) - 1 == ft_strlen(av[2]))
		return (unlink(ptr), open_file(ptr, ptr1));
	while (ptr)
	{
		ptr1 = ft_strjoin(ptr1, ptr);
		if (!ptr1)
			return (free(ptr), -1);
		free(ptr);
		ptr = get_next_line(0);
		if (!ptr)
			return (free(ptr1), -1);
		if (ft_strnstr(ptr, av[2], ft_strlen(av[2])) && \
		ft_strlen(ptr) - 1 == ft_strlen(av[2]))
			break ;
	}
	return (unlink(ptr), open_file(ptr, ptr1));
}

t_list	*ft_init1(int ac, char **av, char **env)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		(error(5), exit(1));
	list->ac = ac;
	list->av = av;
	list->env = env;
	list->in = create_file(av);
	list->out = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	list->stdin = dup(0);
	list->pid = 0;
	return (list);
}

int	here_doc(int ac, char **av, char **env)
{
	t_list	*list;

	list = ft_init1(ac, av, env);
	first_proc(list, av[3]);
	(dup2(list->fd[0], 0), close(list->fd[0]), close(list->fd[1]));
	fpipe(list, 3);
	last_proc(list, av[ac - 2]);
	dup2(list->stdin, 0);
	close(list->stdin);
	close(list->out);
	return (ft_wait(list, 0));
}
