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
		ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
	if (dup2(fd[1], STDIN_FILENO) == -1)
		ft_error(DUP_ERR, DUP_STAT);
	if (close(fd[1]) == -1)
		ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
}

pid_t	out_process(char *command, char **env, int file_out, pid_t **arr)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		ft_error(PIPE_CREATE_ERR, PIPE_CREATE_STAT);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_CREATE_ERR, FORK_CREATE_STAT);
	if (pid == 0)
	{
		free(*arr);
		if (close(fd[1]) == -1)
			ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
		if (dup2(file_out, STDOUT_FILENO) == -1)
			ft_error(DUP_ERR, DUP_STAT);
		if (close(fd[0]) == -1)
			ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
		execute(command, env);
	}
	else
		close_parent(fd);
	return (pid);
}
