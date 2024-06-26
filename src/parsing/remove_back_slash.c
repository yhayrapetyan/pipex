/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_back_slash.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:31 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:33 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_bslash_count(char *quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (quote[i])
	{
		i++;
		if (quote[i] == '\\')
			continue ;
		count++;
	}
	return (count);
}

char	*remove_back_slash(char *quote)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	count = get_bslash_count(quote);
	res = (char *)malloc(sizeof(char) * (count + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (quote[i])
	{
		if (quote[i] != '\\')
		{
			res[j] = quote[i];
			j++;
		}
		i++;
	}
	res[j] = '\0';
	return (res);
}
