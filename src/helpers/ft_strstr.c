/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:27:13 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:27:14 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	substring_len(char *search_in, char *to_find)
{
	int	i;

	i = 0;
	while (to_find[i] != '\0')
	{
		if (search_in[i] != to_find[i])
			return (0);
		i++;
	}
	return (i);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	i;

	i = 0;
	if (to_find[i] == '\0')
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			if (substring_len(str + i, to_find))
				return (str + i);
		}
		i++;
	}
	return (0);
}
