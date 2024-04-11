/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_descriptor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:24:50 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:24:52 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_descriptor(char *file_name, char c)
{
	int	descriptor;

	descriptor = -1;
	if (c == 'H')
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (c == 'O')
	{
		if (access(file_name, F_OK) == 0 && access(file_name, W_OK) != 0)
			ft_error(WRT_PERM_ERR, WRT_PERM_STAT);
		descriptor = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (c == 'I')
		descriptor = open(file_name, O_RDONLY);
	if (descriptor == -1)
		ft_error(FILE_OPEN_ERR, FILE_OPEN_STAT);
	return (descriptor);
}
