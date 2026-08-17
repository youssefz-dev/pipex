/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:23:11 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/12 12:27:45 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_list
{
	int		in;
	int		out;
	int		stdin;
	int		fd[2];
	pid_t	pid;
	int		ac;
	char	**av;
	char	**env;
}				t_list;

char	**ft_split(char const *s, char c);
char	*ft_strjoin1(char *s1, char *s2);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strdup(char *s1);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
char	*ft_strrchr(char *s, int c);
void	ft_free(char **ptr);
void	error(int i);
void	first_proc(t_list *list);
void	last_proc(t_list *list);
t_list	*ft_init(int ac, char **av, char **env);
void	pipex(char *av, t_list *list, int fd);
int		ft_wait(t_list *list, int i);

#endif