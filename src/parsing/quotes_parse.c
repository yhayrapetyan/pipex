#include "pipex.h"

static char	*remove_quotes(char *command)
{
	int	i;

	i = 0;
	while (command[i] && ft_strlen(command) > 1)
	{
		if (is_quote(command[i]) && command[i - 1] == ' ')
		{
			command[i - 1] = '\0';
			break ;
		}
		i++;
	}
	return (ft_strdup(command));
}

static void	get_name2(Qvars *vars)
{
	int	i;

	i = 0;
	while (vars->result[i])
		i++;
	vars->name = (char **)malloc(sizeof(char *) * (i + 2));
	if (!vars->name)
		clean_and_exit(&vars->content, &vars->temp, &vars->result, NULL);
	vars->name[i + 1] = NULL;
	vars->name[i] = ft_strdup(vars->content);
	if (!vars->name[i])
		clean_and_exit(&vars->content, &vars->temp, &vars->result, &vars->name);
	i--;
	while (i >= 0)
	{
		vars->name[i] = ft_strdup(vars->result[i]);
		if (!vars->name[i])
			clean_and_exit(&vars->content, &vars->temp, &vars->result, &vars->name);
		i--;
	}
	clean_vars(&(vars->content), &(vars->temp), &(vars->result), NULL);
}

char	**quotes_parse(char *command)
{
	Qvars	vars;

	vars = init_vars();
	vars.content = get_quotes_content(command);
	if (!vars.content)
		ft_error("Allocation Error\n", 17);
	vars.bslash_temp = vars.content;
	vars.content = remove_back_slash(vars.content);
	free(vars.bslash_temp);
	if (!vars.content)
		ft_error("Allocation Error\n", 17);
	vars.command_name = remove_quotes(command);
	if (!vars.command_name)
		clean_and_exit(&vars.content, NULL, NULL, NULL);
	vars.temp = ft_split(vars.command_name, ' ');
	free(vars.command_name);
	if (!vars.temp)
		clean_and_exit(&vars.content, NULL, NULL, NULL);
	vars.command_name = get_joined_name(vars.temp);
	if (!vars.command_name)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	vars.result = get_result(vars.command_name, vars.temp);
	free(vars.command_name);
	if (!vars.result)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	get_name2(&vars);
	return (vars.name);
}