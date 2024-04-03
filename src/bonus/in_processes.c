#include "pipex.h"

void	in_processes(char *command, char **env)
{
	pid_t   pid;
	int     fd[2];

	if (pipe(fd) == -1)
		ft_error("Can't create the pipe\n", 17);
	pid = fork();
	if (pid == -1)
		ft_error("Can't create the child process\n", 17);
	if (pid == 0)
	{
		if (close(fd[0]) == -1)
			ft_error("Can't close the pipe\n", 17);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
		execute(command, env);
	}
	else
	{
		if (close(fd[1]) == -1)
			ft_error("Can't close the pipe\n", 17);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
	}
}