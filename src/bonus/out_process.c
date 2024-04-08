/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:29:20 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:29:21 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_parent(int *fd)
{
	if (close(fd[0]) == -1)
		ft_error("Can't close the pipe\n", 17);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		ft_error("Can't duplicate the descriptor\n", 17);
	if (close(fd[1]) == -1)
		ft_error("Can't close the pipe\n", 17);
}

pid_t	out_process(char *command, char **env, int file_out)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error("Can't create the pipe\n", 17);
	pid = fork();
	if (pid == -1)
		ft_error("Can't create the child process\n", 17);
	if (pid == 0)
	{
		if (close(fd[1]) == -1)
			ft_error("Can't close the pipe\n", 17);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
		if (close(fd[0]) == -1)
			ft_error("Can't close the pipe\n", 17);
		execute(command, env);
	}
	else
		close_parent(fd);
	return (pid);
}
