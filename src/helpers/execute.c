#include "pipex.h"

void	execute(char *command, char **env)
{
	Evars	e_vars;

	e_vars.cmd_args = NULL;
	e_vars.cmd_path = NULL;
	e_vars.bin_paths = NULL;
	e_vars.is_allocated = 0;
	get_args(&e_vars, command);
	get_path(&e_vars, env);
	if (execve(e_vars.cmd_path, e_vars.cmd_args, env) == -1)
	{
		free_split(e_vars.cmd_args);
		if (e_vars.is_allocated == 1)
			free(e_vars.cmd_path);
		ft_error("Can't execute the command!\n", 126);
	}
}
