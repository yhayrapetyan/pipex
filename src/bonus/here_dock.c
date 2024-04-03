#include "pipex.h"

static void	get_input( char *limiter, int *fd)
{
	char	*line;

	if (close(fd[0]) == -1)
		ft_error("Can't close the pipe\n", 17);
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
		ft_error("Too few arguments for here_dock\n", 17);
	if (pipe(fd) == -1)
		ft_error("Can't create the pipe\n", 17);
	pid = fork();
	if (pid == -1)
		ft_error("Can't create the child process\n", 17);
	if (pid == 0)
		get_input(limiter, fd);
	else
	{
		if (close(fd[1]) == -1)
			ft_error("Can't close the pipe\n", 17);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
		if (waitpid(pid, NULL, 0) == -1)
			ft_error("Waitpid Error!\n", 17);
	}
}