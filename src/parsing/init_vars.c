/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:18 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:19 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

Qvars	init_vars(void)
{
	Qvars	vars;

	vars.content = NULL;
	vars.bslash_temp = NULL;
	vars.command_name = NULL;
	vars.temp = NULL;
	vars.cwo = NULL;
	vars.name = NULL;
	return (vars);
}
