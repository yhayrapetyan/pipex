#include "pipex.h"

int	is_relative_path(char *cmd_name)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_name[i])
	{
		if (cmd_name[i] == '/')
			count++;
		i++;
	}
	if (count == 0)
		return (0);
	return (1);
}

int	have_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH="))
			return (1);
		i++;
	}
	return (0);
}

void	execute(char *command, char **env)
{
	char	**cmd_name;
	char	*command_path = NULL;
	int		flag;

	flag = 0;
	cmd_name = get_name(command);
	if (ft_strncmp(cmd_name[0], "./", 2) == 0)
	{
		if (access(cmd_name[0], F_OK) == 0)
			command_path = cmd_name[0];
	}
	else
		command_path = get_path(cmd_name[flag++], env);
	if (command_path == NULL && is_relative_path(cmd_name[0]) && access(cmd_name[0], F_OK) == 0)
		command_path = cmd_name[--flag];
	if (!command_path)
	{
		free_split(cmd_name);
		if (have_path(env))
			ft_error("Command not found!\n", 127);
		exit(0);
		// ft_error("Command not found!\n", 127);
	}
	if (execve(command_path, cmd_name, env) == -1)
	{
		free_split(cmd_name);
		if (flag == 1)
			free(command_path);
		ft_error("Can't execute the command!\n", 126);
	}
}
