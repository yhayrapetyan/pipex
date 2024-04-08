/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_with_options.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:27:54 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:27:55 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*rm_bslash(char *command_name)
{
	int	i;

	i = 0;
	while (command_name[i])
	{
		if (command_name[i] == '\\')
			command_name[i] = ' ';
		i++;
	}
	return (command_name);
}

static void	get_indexes(char **arr, Ovars *o_vars)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (arr[len])
		len++;
	while (arr[i] && ft_strchr(arr[i], '\\'))
		i++;
	o_vars->i = i;
	o_vars->len = len;
}

char	**get_command_with_options(char *command_name, char **arr)
{
	Ovars	var;

	get_indexes(arr, &var);
	var.result = (char **)malloc(sizeof(char *) * (var.len - var.i + 1));
	if (!var.result)
		return (NULL);
	var.result[var.len - var.i] = NULL;
	while (var.len-- - var.i > 1)
	{
		var.result[var.len - var.i] = ft_strdup(arr[var.len]);
		if (var.result[var.len - var.i] == NULL)
		{
			free_split(var.result);
			return (NULL);
		}
	}
	command_name = rm_bslash(command_name);
	var.result[0] = ft_strdup(command_name);
	return (var.result);
}
