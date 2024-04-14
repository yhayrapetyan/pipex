/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:25:07 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:25:09 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_Bvars	init_bvars(void)
{
	t_Bvars	vars;

	vars.i = 2;
	vars.j = 0;
	return (vars);
}

static void	wait_for_childes(t_Bvars *vars)
{
	vars->i = 0;
	while (vars->i <= vars->j)
	{
		if (waitpid(vars->status_arr[vars->i], &vars->status, 0) == -1)
		{
			free(vars->status_arr);
			ft_error(WAIT_ERR, WAIT_STAT);
		}
		vars->i++;
	}
	free(vars->status_arr);
	if (vars->status != 0)
		exit((vars->status >> 8) & 0xFF);
}

static void	start_pipex_bonus(int ac, char **av, char **env)
{
	t_Bvars	vars;

	vars = init_bvars();
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		vars.out_file = get_descriptor(av[ac - 1], 'H');
		here_doc(av[2], ac);
		vars.i++;
	}
	else
		vars.out_file = get_descriptor(av[ac - 1], 'O');
	vars.status_arr = (pid_t *)malloc(sizeof(pid_t) * (ac - 3));
	if (vars.status_arr == NULL)
		ft_error(MALLOC_ERR, MALLOC_STAT);
	while (vars.i < ac - 2)
	{
		vars.status_arr[vars.j] = in_processes(av, env, vars.i, &vars.status_arr);
		vars.i++;
		vars.j++;
	}
	vars.status_arr[vars.j] = out_process(av[vars.i], env, vars.out_file, &vars.status_arr);
	wait_for_childes(&vars);
}

int	main(int ac, char **av, char **env)
{
	if (ac >= 5 && env)
		start_pipex_bonus(ac, av, env);
	else
		ft_error(ARG_ERR, ARG_STAT);
	return (0);
}
