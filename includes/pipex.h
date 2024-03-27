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
void	free_split(char **str);
void	ft_error(char *message, int status);
char	**ft_split(char const *s, char c);
char	*ft_strstr(char *str, char *to_find);
char	*ft_strjoin(char *s1, char *s2);

void    execute(char *command, char **env);

// VALIDATION
char    *get_path(char *command_name, char **env);
char    *check_command_access(char *cmd_name, char **paths);
#endif
