#include "pipex.h"

char	*get_bin_path(Evars *e_vars, char **env)
{
	char	*command_path;
	int		i;

	i = 0;
	while (env[i] && !ft_strstr(env[i], "PATH="))
		i++;
	if (!env[i])
		return (NULL);
	e_vars->bin_paths = ft_split(env[i] + 5, ':');
	if (e_vars->bin_paths == NULL)
		clean_and_exit(NULL, &e_vars->cmd_args, NULL, NULL);
	command_path = check_command_access(e_vars);
	free_split(e_vars->bin_paths);
	return (command_path);
}
