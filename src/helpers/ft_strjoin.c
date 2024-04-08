/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:26:39 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:26:40 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ch;
	int		i;
	int		size1;
	int		size2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	ch = (char *)malloc(sizeof(char) * (size1 + size2 + 1));
	if (ch == NULL)
		return (NULL);
	i = -1;
	while (s1[++i])
		ch[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		ch[size1] = s2[i];
		size1 ++;
	}
	ch[size1] = '\0';
	return (ch);
}
