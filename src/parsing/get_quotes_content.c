/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_quotes_content.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhayrap <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:28:13 by yuhayrap          #+#    #+#             */
/*   Updated: 2024/04/08 18:28:14 by yuhayrap         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static Cvars	init_cvars(char *command)
{
	Cvars	var;

	var.start = 0;
	var.end = ft_strlen(command);
	var.first_quote = '\0';
	return (var);
}

static void	function_for_norm(Cvars *var, char *command)
{
	while (--var->end >= 0 && command[var->end] == var->quote)
		;
	if (var->end + 1 != var->start)
		var->real_end = var->end;
}

char	*get_quotes_content(char *command)
{
	Cvars	var;

	var = init_cvars(command);
	while (var.start <= var.end)
	{
		while (command[var.start] && var.start < var.end)
		{
			if (is_quote(command[var.start]))
			{
				if (var.first_quote == '\0')
					var.first_quote = command[var.start];
				if (command[var.start] != var.first_quote)
					return (ft_strndup(command + var.start,
							var.end - var.start + 1));
				var.quote = command[var.start];
				var.start++;
				break ;
			}
			var.start++;
		}
		function_for_norm(&var, command);
		if (!is_quote(command[var.start]))
			break ;
	}
	return (ft_strndup(command + var.start, var.real_end - var.start + 1));
}
