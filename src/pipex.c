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
		ft_error("Can't open the file in second\n", 17);
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	if (dup2(pipe[0], STDIN_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n", 17);
	if (dup2(descriptor, STDOUT_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n", 17);
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	execute(av[3], env);
	//idk 
	// if (close(descriptor) == -1)
	// 	ft_error("Can't close the file\n");
}

void	first_child_process(char **av, char **env, int *pipe)
{
	int	descriptor;

	descriptor = open(av[1], O_RDONLY, 0777);
	if (descriptor == -1)
		ft_error("Can't open the file in first child\n", 17);
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n", 17);
	if (dup2(descriptor, STDIN_FILENO) == -1)
		ft_error("Can't dublicate the descriptor\n", 17);
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	execute(av[2], env);
}

int	main(int ac, char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	if (ac > 4)
	{
		if (pipe(fd) == -1)
			ft_error("Can't create the pipe\n", 17);
		pid1 = fork();
		if (pid1 == -1)
			ft_error("Can't create the child process\n", 17);
		if (pid1 == 0)
			first_child_process(av, env, fd);
		else
		{
			pid2 = fork();
			if (pid2 == -1)
				ft_error("Can't create the child process\n", 17);
			if (pid2 == 0)
				second_child_process(av, env, fd);
		}
		if (close(fd[0]) == -1 || close(fd[1]) == -1)
			ft_error("Can't close the pipe\n", 17);
		if (!(pid1 == 0 && pid2 == 0))
		{
			if (waitpid(pid1, &status, 0) == -1)
				ft_error("Waitpid Error!\n", 17);
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			// if (status != pid1)
			// 	exit(3);
			if (waitpid(pid2, &status, 0) == -1)
				ft_error("Waitpid Error!\n", 17);
			if (WIFEXITED(status))
				exit(WEXITSTATUS(status));
			// if (status != pid2)
			// 	exit(EXIT_FAILURE);
		}
	}
	else
		ft_error("Invalid number of arguments\n", 127);
	return (0);
}
