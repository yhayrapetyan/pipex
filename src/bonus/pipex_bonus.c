#include "pipex.h"

static void	start_pipex_bonus(int ac, char **av, char **env)
{
	int		in_file;
	int		out_file;
	int		i;
	int		j;
	int		status;
	pid_t	*status_arr;

	i = 2;
	j = 0;
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		out_file = get_descriptor(av[ac - 1], 'H');
		here_doc(av[2], ac);
		i++;
	}
	else
	{
		in_file = get_descriptor(av[1], 'I');
		out_file = get_descriptor(av[ac - 1], 'O');
		if (dup2(in_file, STDIN_FILENO) == -1)
			ft_error("Can't duplicate the descriptor\n", 17);
	}
	status_arr = (pid_t *)malloc(sizeof(pid_t) * (ac - 3));
	if (status_arr == NULL)
		ft_error("Allocation failed\n", 17);
	while (i < ac - 2)
	{
		status_arr[j] = in_processes(av[i], env);
		i++;
		j++;
	}
	status_arr[j] = out_process(av[i], env, out_file);
	i = 0;
	while (i < j)
	{
		if (waitpid(status_arr[i], NULL, 0) == -1)
			ft_error("Waitpid Error!\n", 17);
		i++;
	}
	if (waitpid(status_arr[i], &status, 0) == -1)
		ft_error("Waitpid Error!\n", 17);
	if (status != 0)
		exit(WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	if (ac >= 5 && env)
		start_pipex_bonus(ac, av, env);
	else
		ft_error("Invalid number of arguments\n", 127);
	return (0);
}