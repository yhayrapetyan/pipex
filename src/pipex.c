/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:07:37 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/03/20 18:07:39 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


void	second_child_process(char **av, char **env, int *pipe)
{
	int	descriptor;

	descriptor = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (descriptor == -1)
		ft_error("Can't open the file\n");
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n");
	if (dup2(pipe[0], STDIN_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n");
	if (dup2(descriptor, STDOUT_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n");
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n");
	execute(av[3], env);
	//idk 
	// if (close(descriptor) == -1)
	// 	ft_error("Can't close the file\n");
}

void	first_child_process(char **av, char **env, int *pipe)
{
	int	descriptor;

	descriptor = open(av[1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (descriptor == -1)
		ft_error("Can't open the file\n");
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n");
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n");
	if (dup2(descriptor, STDIN_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n");
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n");
	execute(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	// int		status;

	if (ac > 4)
	{
		if (pipe(fd) == -1)
			ft_error("Can't create the pipe\n");
		pid1 = fork();
		if (pid1 == -1)
			ft_error("Can't create the child process\n");
		if (pid1 == 0)
			first_child_process(av, env, fd);
		else
		{
			pid2 = fork();
			if (pid2 == -1)
				ft_error("Can't create the child process\n");
			if (pid2 == 0)
				second_child_process(av, env, fd);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			ft_error("Can't close the pipe\n");
	}
	else
		ft_error("Invalid number of arguments\n");
	return (0);
}
