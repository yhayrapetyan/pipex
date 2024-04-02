#include "pipex.h"

static char	*get_joined_name(char **arr)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = ft_strjoin("", arr[0]);
	while (arr[i] && ft_strchr(arr[i], '\\'))
	{
		temp = ft_strjoin(result, arr[i + 1]);
		free(result);
		result = temp;
		i++;
	}
	return (result);
}

static char	**get_result(char *command_name, char **arr)
{
	char	**result;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (arr[len])
		len++;
	while (arr[i] && ft_strchr(arr[i], '\\'))
		i++;
	result = (char **)malloc(sizeof(char *) * (len - i + 1));
	result[len - i] = NULL;
	while (len-- - i > 0)
		result[len - i] = ft_strdup(arr[len]);
	i = 0;
	while (command_name[i])
	{
		if (command_name[i] == '\\')
			command_name[i] = ' ';
		i++;
	}
	result[0] = ft_strdup(command_name);
	return (result);
}

char	**get_name(char *command)
{
	char	**temp;
	char	*command_name;
	char	**result;

	temp = ft_split(command, ' ');
	command_name = get_joined_name(temp);
	result = get_result(command_name, temp);
	free(command_name);
	free_split(temp);
	return (result);
}