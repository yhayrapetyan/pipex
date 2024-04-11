/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_dock.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:56 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:24:58 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_input( char *limiter, int *fd)
{
	char	*line;

	if (close(fd[0]) == -1)
		ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDERR_FILENO);
	}
}

void	here_doc(char *limiter, int argc)
{
	pid_t	pid;
	int		fd[2];

	if (argc < 6)
		ft_error("Too few arguments for here_dock\n", 13);
	if (limiter == NULL || *limiter == '\0')
		ft_error("Invalid Limiter\n", 14);
	if (pipe(fd) == -1)
		ft_error(PIPE_CREATE_ERR, PIPE_CREATE_STAT);
	pid = fork();
	if (pid == -1)
		ft_error(FORK_CREATE_ERR, PIPE_CREATE_STAT);
	if (pid == 0)
		get_input(limiter, fd);
	else
	{
		if (close(fd[1]) == -1)
			ft_error(PIPE_CLOSE_ERR, PIPE_CLOSE_STAT);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error(DUP_ERR, DUP_STAT);
		if (waitpid(pid, NULL, 0) == -1)
			ft_error(WAIT_ERR, WAIT_STAT);
	}
}
