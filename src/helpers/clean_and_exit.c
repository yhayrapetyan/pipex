#include "pipex.h"

void	clean_and_exit(char **content, char ***temp, char ***result, char ***name)
{
	if (content != NULL)
		free(*content);
	if (temp != NULL)
		free_split(*temp);
	if (result != NULL)
		free_split(*result);
	if (name != NULL)
		free_split(*name);
	ft_error("Allocation Error\n", 17);
}