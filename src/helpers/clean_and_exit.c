/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:25:39 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:25:40 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_and_exit(char **content, char ***temp, char ***res, char ***name)
{
	if (content != NULL)
		free(*content);
	if (temp != NULL)
		free_split(*temp);
	if (res != NULL)
		free_split(*res);
	if (name != NULL)
		free_split(*name);
	ft_error(MALLOC_ERR, MALLOC_STAT);
}
