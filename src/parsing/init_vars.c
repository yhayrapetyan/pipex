#include "pipex.h"

Qvars	init_vars(void)
{
	Qvars	vars;

	vars.content = NULL;
	vars.bslash_temp = NULL;
	vars.command_name = NULL;
	vars.temp = NULL;
	vars.result = NULL;
	vars.name = NULL;
	return (vars);
}