#include "pipex.h"

char	**simple_parse(char *command)
{
	Qvars	vars;

	vars = init_vars();
	vars.content = remove_back_slash(command);
	if (!vars.content)
		ft_error("Allocation Error\n", 17);
	vars.temp = ft_split(vars.content, ' ');
	if (!vars.temp)
		clean_and_exit(&vars.content, NULL, NULL, NULL);
	vars.command_name = get_joined_name(vars.temp);
	if (!vars.command_name)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	vars.name = get_command_with_options(vars.command_name, vars.temp);
	if (!vars.name)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	clean_vars(&vars.content, &vars.temp, NULL, NULL);
	return (vars.name);
}