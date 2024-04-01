#include "pipex.h"

void	execute(char *command, char **env)
{
	char	**cmd_name;
	char	*command_path;
	int		flag;

	flag = 0;
	fprintf(stderr, "\n\n\n raw = %s\n\n\n\n", command);
	fprintf(stderr, "❌❌❌❌❌❌❌❌❌❌❌❌❌❌❌❌❌\n");
	cmd_name = ft_split(command, ' ');
	fprintf(stderr, "name = %s\n", cmd_name[0]);
	if (ft_strncmp(cmd_name[0], "./", 2) == 0 && access(cmd_name[0], X_OK) == 0)
		command_path = cmd_name[0];
	else
		command_path = get_path(cmd_name[flag++], env);
	if (command_path == NULL && access(cmd_name[0], X_OK) == 0)
		command_path = cmd_name[--flag];
	fprintf(stderr, "path = %s\n", command_path);
	int	i = 0;
	while (cmd_name[i])
	{
		fprintf(stderr, "name[%d] = %s\n",i , cmd_name[i]);
		i++;
	}
	if (!command_path)
	{
		free_split(cmd_name);
		ft_error("Command not found!\n", 127);
	}
	fprintf(stderr, "🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶🔶\n");
	if (execve(command_path, cmd_name, env) == -1)
	{
		fprintf(stderr, "🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵🔵\n");
		free_split(cmd_name);
		if (flag == 1)
			free(command_path);
		ft_error("Can't execute the command!\n", 17);
	}
	fprintf(stderr, "✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅✅\n");
}