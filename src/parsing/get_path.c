#include "pipex.h"

char	*get_bin_path(char *command_name, char **env)
{
	char	*command_path;
	char	**bin_paths;
	int		i;

	i = 0;
	bin_paths = NULL;
	while (env[i] && !ft_strstr(env[i], "PATH="))
		i++;
	if (!env[i])
		return (NULL);
	bin_paths = ft_split(env[i] + 5, ':');
	command_path = check_command_access(command_name, bin_paths);
	free_split(bin_paths);
	return (command_path);
}
