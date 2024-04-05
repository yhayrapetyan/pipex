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

	if (access(av[4], F_OK) == 0 && access(av[4], W_OK) != 0)
		ft_error("No write permission\n", 1);
	descriptor = open(av[4],O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// fprintf(stderr, "descript = %d\n", descriptor);
	// descriptor = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (descriptor == -1)
		ft_error("Can't open the file in second child\n", 17);
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	if (dup2(pipe[0], STDIN_FILENO) == -1)
		ft_error("Can't duplicate the descriptor\n", 17);
	if (dup2(descriptor, STDOUT_FILENO) == -1)
		ft_error("Can't duplicate the descriptor\n", 17);
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	execute(av[3], env);
}

void	first_child_process(char **av, char **env, int *pipe)
{
	int	descriptor;

	descriptor = open(av[1], O_RDONLY);
	if (descriptor == -1)
		ft_error("Can't open the file in first child\n", 17);
	if (close(pipe[0]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	if (dup2(pipe[1], STDOUT_FILENO) == -1)
		ft_error("Can't duplicate the descriptor\n", 17);
	if (dup2(descriptor, STDIN_FILENO) == -1)
		ft_error("Can't duplicate the descriptor\n", 17);
	if (close(pipe[1]) == -1)
		ft_error("Can't close the pipe in child\n", 17);
	execute(av[2], env);
}

void	start_pipex(char **av, char **env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;
	int		status;

	status = 0;
	if (pipe(fd) == -1)
		ft_error("Can't create the pipe\n", 17);
	pid1 = fork();
	pid2 = fork();
	if (pid1 == -1 || pid2 == -1)
		ft_error("Can't create the child process\n", 17);
	if (pid1 == 0 && pid2 != 0)
		first_child_process(av, env, fd);
	if (pid1 != 0 && pid2 == 0)
		second_child_process(av, env, fd);
	if (close(fd[0]) == -1 || close(fd[1]) == -1)
		ft_error("Can't close the pipe\n", 17);
	if (pid1 != 0 && pid2 != 0)
	{
		if (waitpid(pid1, NULL, 0) == -1)
			ft_error("Waitpid Error!\n", 16);
		if (waitpid(pid2, &status, 0) == -1)
			ft_error("Waitpid Error!\n", 17);
		if (status != 0)
			exit(WEXITSTATUS(status));
			// exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	// int	i = 0;
	// (void)env;
	// (void)ac;
	// while (av[1][i])
	// {
	// 	printf("%c\n", av[1][i]);
	// 	i++;
	// }
	// char	*arr[3] = {"cat", "hello -e", NULL};
	// execve("/usr/bin/cat", arr, env);
	if (ac == 5 && env)
		start_pipex(av, env);
	else
		ft_error("Invalid number of arguments\n", 127);
	return (0);
}
