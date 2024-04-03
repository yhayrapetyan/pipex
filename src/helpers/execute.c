#include "pipex.h"


void	execute(char *command, char **env)
{
	char	**cmd_name;
	char	*command_path = NULL;
	int		flag;

	flag = 0;
	cmd_name = get_name(command);
	if (ft_strncmp(cmd_name[0], "./", 2) == 0)
	{
		if (access(cmd_name[0], X_OK) == 0)
			command_path = cmd_name[0];
	}
	else
		command_path = get_path(cmd_name[flag++], env);
	if (command_path == NULL && access(cmd_name[0], X_OK) == 0)
		command_path = cmd_name[--flag];
	if (!command_path)
	{
		free_split(cmd_name);
		ft_error("Command not found!\n", 127);
	}
	if (execve(command_path, cmd_name, env) == -1)
	{
		free_split(cmd_name);
		if (flag == 1)
			free(command_path);
		ft_error("Can't execute the command!\n", 17);
	}
}
