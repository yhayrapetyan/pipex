/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_built_in_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:19:24 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/15 11:19:26 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**clean_malloc(char **result, int len)
{
	int	i;

	i = 2;
	while (i < len)
	{
		free(result[i]);
		i++;
	}
	return (NULL);
}

char	**get_built_in_args(char **cmd_args)
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
		result[i + 1] = ft_strdup(cmd_args[i - 1]);
		if (!result[i + 1])
			return (clean_malloc(result, i + 1));
		i--;
	}
	return (result);
}
