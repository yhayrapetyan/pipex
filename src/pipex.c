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
	Pvars	p_vars;

	p_vars.status = 0;
	if (pipe(p_vars.fd) == -1)
		ft_error("Can't create the pipe\n", 17);
	p_vars.pid1 = fork();
	p_vars.pid2 = fork();
	if (p_vars.pid1 == -1 || p_vars.pid2 == -1)
		ft_error("Can't create the child process\n", 17);
	if (p_vars.pid1 == 0 && p_vars.pid2 != 0)
		first_child_process(av, env, p_vars.fd);
	if (p_vars.pid1 != 0 && p_vars.pid2 == 0)
		second_child_process(av, env, p_vars.fd);
	if (close(p_vars.fd[0]) == -1 || close(p_vars.fd[1]) == -1)
		ft_error("Can't close the pipe\n", 17);
	if (p_vars.pid1 != 0 && p_vars.pid2 != 0)
	{
		if (waitpid(p_vars.pid1, NULL, 0) == -1)
			ft_error("Waitpid Error!\n", 16);
		if (waitpid(p_vars.pid2, &p_vars.status, 0) == -1)
			ft_error("Waitpid Error!\n", 17);
		if (p_vars.status != 0)
			exit(WEXITSTATUS(p_vars.status));
			// exit(1);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5 && env)
		start_pipex(av, env);
	else
		ft_error("Invalid number of arguments\n", 127);
	return (0);
}
