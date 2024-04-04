/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:07:30 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/03/20 18:07:31 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>//delete
# include <stdlib.h>
#include <sys/wait.h>

# define RED "\033[1;31m"
# define YELLOW "\033[1;33m"
# define RESET_COLOR "\033[0m"
# define GREEN "\033[1;32m"

// HELPERS
int     ft_strlen(char *str);
char	*ft_strndup(const char *str, int n);
void	free_split(char **str);
void	ft_error(char *message, int status);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
int		ft_strchr(char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strtrim(char *s1, char *set);
int	    ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin(char *s1, char *s2);

void	execute(char *command, char **env);
char	**get_name(char *command);

// VALIDATION
char    *get_path(char *command_name, char **env);
char    *check_command_access(char *cmd_name, char **paths);

// BONUS
int		get_descriptor(char *file_name, char c);
void	in_processes(char *command, char **env);
pid_t	out_process(char *command, char **env, int file_out);
void	here_doc(char *limiter, int argc);

// GNL
char	*get_next_line(int fd);
char	*gnl_strjoin(char *s1, char *s2);
char	*get_line(char *str);
char	*get_new_left_str(char *str);

#endif
