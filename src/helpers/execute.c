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
	e_vars.is_path_allocated = 0;
	return (e_vars);
}

static void	clean_evars(t_Evars *e_vars)
{
	free_split(e_vars->cmd_args);
	if (e_vars->is_path_allocated == 1)
		free(e_vars->cmd_path);
}

void	execute(char *command, char **env)
{
	t_Evars	e_vars;
	char	**temp;

	e_vars = init_evars();
	get_args(&e_vars, command);
	get_path(&e_vars, env);
	if (ft_strncmp(e_vars.cmd_path, "/bin/sh", ft_strlen("/bin/sh") + 1) == 0)
	{
		temp = e_vars.cmd_args;
		e_vars.cmd_args = get_built_in_args(e_vars.cmd_args);
		free_split(temp);
		if (!e_vars.cmd_args)
		{
			clean_evars(&e_vars);
			ft_error(MALLOC_ERR, MALLOC_STAT);
		}
	}
	if (execve(e_vars.cmd_path, e_vars.cmd_args, env) == -1)
	{
		clean_evars(&e_vars);
		ft_error(EXEC_ERR, EXEC_STAT);
	}
}
