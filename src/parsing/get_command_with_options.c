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

char	**get_command_with_options(char *command_name, char **arr)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (arr[len])
		len++;
	while (arr[i] && ft_strchr(arr[i], '\\'))
		i++;
	result = (char **)malloc(sizeof(char *) * (len - i + 1));
	if (!result)
		return (NULL);
	result[len - i] = NULL;
	while (len-- - i > 1)
	{
		result[len - i] = ft_strdup(arr[len]);
		if (result[len - i] == NULL)
		{
			free_split(result);
			return (NULL);
		}
	}
	command_name = rm_bslash(command_name);
	result[0] = ft_strdup(command_name);
	return (result);
}
