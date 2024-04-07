#include "pipex.h"

char    *check_command_access(Evars *e_vars)
{
	char	*cmd_path;
	char	*temp;
	int		i;

	i = 0;
	while (e_vars->bin_paths[i])
	{
		temp = ft_strjoin(e_vars->bin_paths[i], "/");
		if (temp == NULL)
			clean_and_exit(NULL, &e_vars->cmd_args, &e_vars->bin_paths, NULL);
		cmd_path = ft_strjoin(temp, e_vars->cmd_args[0]);
		free(temp);
		if (cmd_path == NULL)
			clean_and_exit(NULL, &e_vars->cmd_args, &e_vars->bin_paths, NULL);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}