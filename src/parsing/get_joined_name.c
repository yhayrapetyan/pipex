/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_joined_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:00 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:02 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_joined_name(char **arr)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = NULL;
	result = ft_strjoin("", arr[0]);
	while (arr[i] && ft_strchr(arr[i], '\\'))
	{
		temp = ft_strjoin(result, arr[i + 1]);
		free(result);
		result = temp;
		i++;
	}
	return (result);
}
