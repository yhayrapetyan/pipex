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

// void	parse_text(const char *text)
// {
// 	const char	*start = NULL;
// 	const char	*end = NULL;
// 	char		*result;
// 	int			length;
// 	int			inside_quotes;
// 	int			i;

// 	i = 0;
// 	inside_quotes = 0;
// 	while (text[i] != '\0')
// 	{
// 		if (!inside_quotes && (text[i] == '"' || text[i] == '\''))
// 		{
// 			inside_quotes = 1;
// 			start = &text[i];
// 		}
// 		else if (inside_quotes && (text[i] == '"' || text[i] == '\''))
// 		{
// 			if (*(start) == text[i] && ((start - 1) < &text[i]))
// 			{
// 				end = &text[i];
// 				inside_quotes = 0;
// 				break ;
// 			}
// 		}
// 		i++;
// 	}

// 	if (start != NULL && end != NULL)
// 	{
// 		length = end - start - 1;
// 		result = (char *)malloc((length + 1) * sizeof(char));
// 		if (result != NULL)
// 		{
// 			strncpy(result, start + 1, length);
// 			result[length] = '\0';
// 			printf("Extracted text: %s\n", result);
// 			free(result);
// 		}
// 		else
// 		{
// 			printf("Memory allocation failed.\n");
// 		}
// 	}
// 	else
// 	{
// 		printf("No text found within quotes.\n");
// 	}
// }

// char	*get_inside_quotes(char	*command)
// {
// 	int	single_q;
// 	int	double_q;
// 	int	i;

// 	single_q = 0;
// 	double_q = 0;
// 	i = 0;
// 	while (command[i])
// 	{
// 		if (command[i] == '\'')
// 			single_q++;
// 		if (command[i] == '"')
// 			double_q++;
// 		i++;
// 	}
// 	if()


// }

char	**get_name(char *command)
{
	char	**temp;
	char	*command_name;
	char	**result;
	// char	*inside_quotes;

	// inside_quotes = get_inside_quotes(command);
	// command = rm_qoutes(command);
	temp = ft_split(command, ' ');
	command_name = get_joined_name(temp);
	result = get_result(command_name, temp);
	free(command_name);
	free_split(temp);
	return (result);
}