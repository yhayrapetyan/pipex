/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:23 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:26 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*remove_quotes(char *command)
{
	int	i;

	i = 0;
	while (command[i] && ft_strlen(command) > 1)
	{
		if (is_quote(command[i]) && command[i - 1] == ' ')
		{
			command[i - 1] = '\0';
			break ;
		}
		i++;
	}
	return (ft_strdup(command));
}

static void	get_result(t_Qvars *vars)
{
	int	i;

	i = 0;
	while (vars->cwo[i])
		i++;
	vars->name = (char **)malloc(sizeof(char *) * (i + 2));
	if (!vars->name)
		clean_and_exit(&vars->content, &vars->temp, &vars->cwo, NULL);
	vars->name[i + 1] = NULL;
	vars->name[i] = ft_strdup(vars->content);
	if (!vars->name[i])
		clean_and_exit(&vars->content, &vars->temp, &vars->cwo, &vars->name);
	i--;
	while (i >= 0)
	{
		vars->name[i] = ft_strdup(vars->cwo[i]);
		if (!vars->name[i])
			clean_and_exit(&vars->content, &vars->temp,
				&vars->cwo, &vars->name);
		i--;
	}
	clean_vars(&(vars->content), &(vars->temp), &(vars->cwo), NULL);
}

static void	function_for_norm(char *content, t_Qvars *vars)
{
	if (!content)
		ft_error(MALLOC_ERR, MALLOC_STAT);
	vars->bslash_temp = vars->content;
}

char	**quotes_parse(char *command)
{
	t_Qvars	vars;

	vars = init_vars();
	vars.content = get_quotes_content(command);
	function_for_norm(vars.content, &vars);
	vars.content = remove_back_slash(vars.content);
	free(vars.bslash_temp);
	if (!vars.content)
		ft_error(MALLOC_ERR, MALLOC_STAT);
	vars.command_name = remove_quotes(command);
	if (!vars.command_name)
		clean_and_exit(&vars.content, NULL, NULL, NULL);
	vars.temp = ft_split(vars.command_name, ' ');
	free(vars.command_name);
	if (!vars.temp)
		clean_and_exit(&vars.content, NULL, NULL, NULL);
	vars.command_name = get_joined_name(vars.temp);
	if (!vars.command_name)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	vars.cwo = get_command_with_options(vars.command_name, vars.temp);
	free(vars.command_name);
	if (!vars.cwo)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	get_result(&vars);
	return (vars.name);
}
