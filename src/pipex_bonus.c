#include "pipex.h"

int	get_descriptor(char *file_name, char c)
{
	int	descriptor;

	descriptor = -1;
	if (c == 'H')
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (c == 'O')
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'I')
		descriptor = open(file_name, O_RDONLY, 0777);
	if (descriptor == -1)
		ft_error("Can't open the file\n", 17);
	return (descriptor);
}

void	start_pipex_bonus(int ac, char **av, char **env)
{
	int	in_file;
	int	out_file;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		here_doc();
	else
	{
		in_file = get_descriptor(av[0], 'I');
		out_file = get_descriptor(av[ac - 1], 'O');
		if (dup2(in_file, STDIN_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
	}
}

int	main(int ac, char **av, char **env)
{
	if (ac >= 5 && av && env)
		start_pipex_bonus(ac, av, env);
	else
		ft_error("Invalid number of arguments\n", 127);
	return (0);
}