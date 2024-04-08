/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:25:45 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:25:47 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_vars(char **content, char ***temp, char ***result, char ***name)
{
	if (content != NULL)
		free(*content);
	if (temp != NULL)
		free_split(*temp);
	(void)content;
	if (result != NULL)
		free_split(*result);
	if (name != NULL)
		free_split(*name);
}
