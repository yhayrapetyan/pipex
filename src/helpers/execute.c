/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:25:52 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:25:53 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_Evars	init_evars(void)
{
	t_Evars	e_vars;

	e_vars.cmd_args = NULL;
	e_vars.cmd_path = NULL;
	e_vars.bin_paths = NULL;
	e_vars.is_allocated = 0;
	return (e_vars);
}

static char **get_built_in_args(char **cmd_args)
{
	int		i;
	char	**result;

	i = 0;
	while (cmd_args[i])
		i++;
	result = (char **)malloc(sizeof(char *) * (i + 3));
	if (!result)
		return (NULL);
	result[0] = "/bin/sh";
	result[1] = "-c";
	result[i + 2] = NULL;
	while (i > 0)
	{
		result[i + 1] = cmd_args[i - 1];
		i--;
	}
	return (result);
}


void	execute(char *command, char **env)
{
	t_Evars	e_vars;

	e_vars = init_evars();
	get_args(&e_vars, command);
	get_path(&e_vars, env);
	if (ft_strncmp(e_vars.cmd_path, "/bin/sh", ft_strlen("/bin/sh") + 1) == 0)
	{
		e_vars.cmd_args = get_built_in_args(e_vars.cmd_args);
		if (!e_vars.cmd_args)
		{
			free_split(e_vars.cmd_args);
			if (e_vars.is_allocated == 1)
				free(e_vars.cmd_path);
			ft_error("Allocation Failed\n", 17);
		}
	}
	if (execve(e_vars.cmd_path, e_vars.cmd_args, env) == -1)
	{
		free_split(e_vars.cmd_args);
		if (e_vars.is_allocated == 1)
			free(e_vars.cmd_path);
		ft_error("Can't execute the command!\n", 126);
	}
}
