#include "pipex.h"

char    *check_command_access(char *cmd_name, char **bin_paths)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	while (bin_paths[i])
	{
		temp = ft_strjoin(bin_paths[i], "/");
		cmd_path = ft_strjoin(temp, cmd_name);
		free(temp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}