#include "pipex.h"

char    *get_path(char *command_name, char **env)
{
	char	*command_path;
    char	**bin_paths;
	int		i;

	i = 0;
	while (env[i] && !ft_strstr(env[i], "PATH="))
		i++;
	if (!env[i])
		ft_error("Can't find path to bin files\n", 17);
	bin_paths = ft_split(env[i] + 5, ':');
	command_path = check_command_access(command_name, bin_paths);
    if (command_path == NULL && access(command_name, X_OK) == 0)
        return (command_name);
    free_split(bin_paths);
	return (command_path);
}