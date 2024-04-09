/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:07 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:09 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_relative_path(char *cmd_name)
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

static int	have_path(char **env)
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

static int	is_built_in_command(char *command)
{
	const char	*builtin_commands[] = {".", ":", "[", "alias", "bg", "bind",
		"break", "builtin", "caller", "cd", "command", "compgen", "complete",
		"compopt", "continue", "declare", "dirs", "disown", "echo", "enable",
		"eval", "exec", "exit", "export", "false", "fc", "fg", "getopts",
		"hash", "help", "history", "jobs", "kill", "let", "local", "logout",
		"mapfile", "popd", "printf", "pushd", "pwd", "read", "readarray",
		"readonly", "return", "set", "shift", "shopt", "source", "suspend",
		"test", "times", "trap", "true", "type", "typeset", "ulimit", "umask",
		"unalias", "unset", "wait", NULL,
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

static void	get_path_with_env(t_Evars *e_vars, char **env)
{
	if (ft_strncmp(e_vars->cmd_args[0], "./", 2) == 0)
		e_vars->cmd_path = e_vars->cmd_args[0];
	else
	{
		e_vars->is_allocated++;
		e_vars->cmd_path = get_bin_path(e_vars, env);
	}
	if (e_vars->cmd_path == NULL && is_relative_path(e_vars->cmd_args[0]) && \
		access(e_vars->cmd_args[0], F_OK) == 0)
	{
		e_vars->is_allocated--;
		e_vars->cmd_path = e_vars->cmd_args[e_vars->is_allocated];
	}
}

void	get_path(t_Evars *e_vars, char **env)
{
	if (have_path(env))
		get_path_with_env(e_vars, env);
	else
	{
		if (ft_strncmp(e_vars->cmd_args[0], "./", 2) == 0 && \
			access(e_vars->cmd_args[0], F_OK) == 0)
			e_vars->cmd_path = e_vars->cmd_args[0];
		else
		{
			if (is_built_in_command(e_vars->cmd_args[0]))
				ft_error("Command not found!\n", 0);
			if (access(e_vars->cmd_args[0], F_OK) == 0)
				e_vars->cmd_path = e_vars->cmd_args[0];
		}
	}
	if (!e_vars->cmd_path)
	{
		free_split(e_vars->cmd_args);
		ft_error("Command not found!!!\n", 127);
	}
}
