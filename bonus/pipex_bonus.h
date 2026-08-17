/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzoullik <yzoullik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 12:23:11 by yzoullik          #+#    #+#             */
/*   Updated: 2025/03/12 12:45:38 by yzoullik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define BUFFER_SIZE 42

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
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *s);
size_t	ft_strlcpy(char *dst, char *src, size_t dstsize);
char	*ft_strdup(char *s1);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*ft_strnstr(char *haystack, char *needle, size_t len);
int		ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
void	ft_free(char **ptr);
char	*ft_strjoin1(char *s1, char *s2);
int		ft_wait(t_list *list, int i);
char	*get_next_line(int fd);
void	pipex(char *av, t_list *list, int fd);
int		here_doc(int ac, char **av, char **env);
void	ft_putstr_fd(char *s, int fd);
char	*ft_itoa(int n);
void	files_error(int in, int out);
void	files_error1(int in, int out, int pipe, int *fd);
void	error(int i);
t_list	*ft_init(int ac, char **av, char **env);
void	first_proc(t_list *list, char *av);
void	last_proc(t_list *list, char *av);
void	fpipe(t_list *list, int i);

#endif