#include "pipex.h"

void    execute(char *command, char **env)
{
    char    **command_name;
    char    *command_path;

    command_name = ft_split(command, ' ');
    command_path = get_path(command_name[0], env);

    if (!command_path)
    {
        free_split(command_name);
        printf("command_name = %s\n", command_name[0]);
        ft_error("Can't find command!\n");
    }
    if (execve(command_path, command_name, env) == -1)
    {
        free_split(command_name);
        free(command_path);
        ft_error("Can't execute the command\n");
    }
}