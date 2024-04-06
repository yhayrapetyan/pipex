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

int	is_built_in_command(char *command)
{
	const char *builtin_commands[] = {
			".", ":", "[", "alias", "bg", "bind", "break", "builtin", "caller", "cd",
			"command", "compgen", "complete", "compopt", "continue", "declare", "dirs",
			"disown", "echo", "enable", "eval", "exec", "exit", "export", "false", "fc",
			"fg", "getopts", "hash", "help", "history", "jobs", "kill", "let", "local",
			"logout", "mapfile", "popd", "printf", "pushd", "pwd", "read", "readarray",
			"readonly", "return", "set", "shift", "shopt", "source", "suspend", "test",
			"times", "trap", "true", "type", "typeset", "ulimit", "umask", "unalias",
			"unset", "wait", NULL,
	};
	int			i;

	i = 0;
	while (builtin_commands[i])
	{
		if (ft_strncmp(command, builtin_commands[i], ft_strlen(command)) == 0)
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
	if (have_path(env))
	{
		if (ft_strncmp(cmd_name[0], "./", 2) == 0)
		{
			if (access(cmd_name[0], F_OK) == 0)
				command_path = cmd_name[0];
		}
		else
			command_path = get_path(cmd_name[flag++], env);
		if (command_path == NULL && is_relative_path(cmd_name[0]) && access(cmd_name[0], F_OK) == 0)
			command_path = cmd_name[--flag];
	}
	else
	{
		if (ft_strncmp(cmd_name[0], "./", 2) == 0)
		{
			if (access(cmd_name[0], F_OK) == 0)
				command_path = cmd_name[0];
		}
		else
		{
			fprintf(stderr, "command = %s\n", cmd_name[0]);
			if (is_built_in_command(cmd_name[0]))//in built-in
				ft_error("Command not found!\n", 0);
			if (access(cmd_name[0], F_OK) == 0)
				command_path = cmd_name[0];
		}
	}
		if (!command_path)
	{
		free_split(cmd_name);
//		if (!have_path(env))
//			ft_error("No such file or directory\n", 0);
		 ft_error("Command not found!\n", 127);
	}
	if (execve(command_path, cmd_name, env) == -1)
	{
		free_split(cmd_name);
		if (flag == 1)
			free(command_path);
		ft_error("Can't execute the command!\n", 126);
	}
}
