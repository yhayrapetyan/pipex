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
	if (!result)
		ft_error("Allocation Error\n", 17);
	result[len - i] = NULL;
	while (len-- - i > 1)
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

static int	is_quote(char ch)
{
	if (ch == '"' || ch == '\'')
		return (1);
	return (0);
}

char	*parse_quotes(char *command)
{
	int		start;
	int		end;
	int		real_end;
	char	quote;

	start = 0;
	end = ft_strlen(command) - 1;
	while (start <= end)
	{
		while (command[start] && start < end)
		{
			if (is_quote(command[start]))
			{
				quote = command[start];
				start++;
				break ;
			}
			start++;
		}
		while (command[end])
		{
			if (command[end] == quote)
			{
				end--;
				break ;
			}
			end--;
		}
		if (end + 1 != start)
			real_end = end;
		if (!is_quote(command[start]))
			break ;
	}
	return (ft_strndup(command + start, real_end - start + 1));
}

char	*remove_back_slash(char *quote)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	i = 0;
	count = 0;
	while (quote[i])
	{
		i++;
		if (quote[i] == '\\')
			continue ;
		count++;
	}
	res = (char *)malloc(sizeof(char *) * (count + 1));
	if (!res)
		ft_error("Alocation Error\n", 17);
	i = 0;
	j = 0;
	while (quote[i])
	{
		if (quote[i] != '\\')
		{
			res[j] = quote[i];
			j++;
		}
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**get_name(char *command)
{
	char	**temp;
	char	**quote_temp;
	char	*command_name;
	char	*new_command;
	char	*quotes;
	char	*back_temp;
	char	**result;
	char	**name;
	int		single_quote;
	int		double_quote;
	int		i;
	int		j;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	result = NULL;
	// fprintf(stderr, "🔵\n");
	while (command[i])
	{
		// fprintf(stderr, "❗️cmd[%d] = %c\n", i, command[i]);
		if (command[i] == '"')
			double_quote++;
		if (command[i] == '\'')
			single_quote++;
		i++;
	}
	// fprintf(stderr, "s = %d, d = %d\n", single_quote, double_quote);
	i = 0;
	if (single_quote > 1 || double_quote > 1)
	{
		// fprintf(stderr, "✅\n");
		quotes = parse_quotes(command);
		back_temp = quotes;
		quotes = remove_back_slash(quotes);
		free(back_temp);
		fprintf(stderr, "quotes = %s\n", quotes);
		while (command[i] && ft_strlen(command) > 1)
		{
			if (is_quote(command[i]) && command[i - 1] == ' ')
			{
				command[i - 1] = '\0';
				break ;
			}
			i++;
		}
		new_command = ft_strndup(command, i - 1);
		// fprintf(stderr, "command after = %s\n", new_command);
		if (!new_command)
			ft_error("Alocation Error\n", 17);
		temp = ft_split(new_command, ' ');
		quote_temp = ft_split(quotes, ' ');
		if (!quote_temp)
			ft_error("Alocation Error\n", 17);
		command_name = get_joined_name(temp);
		result = get_result(command_name, temp);
		i = 0;
		while (result[i])
			i++;
		// while (quote_temp[j])
		// {
		// 	// fprintf(stderr, "quote_temp[%d] = %s\n", j, quote_temp[j]);
		// 	j++;
		// }
		// fprintf(stderr, "i = %d, j = %d\n", i, j);
		name = (char **)malloc(sizeof(char *) * (i  + 2));//  + j
		if (!name)
			ft_error("Alocation Error\n", 17);
		name[i + j + 1] = NULL;
		name[i + j] = quotes;
		j--;
		// while (j >= 0)
		// {
		// 	// fprintf(stderr, "n = %d\n", i + j);
		// 	name[i + j] = quote_temp[j];
		// 	j--;
		// }
		i--;
		while (i >= 0)
		{
			// fprintf(stderr, "m = %d\n", i);
			name[i] = ft_strdup(result[i]);
			i--;
		}
		// i = 0;
		// while (name[i])
		// {
		// 	fprintf(stderr, "name[%d] = %s\n", i, name[i]);
		// 	i++;
		// }
	}
	else
	{
		temp = ft_split(command, ' ');
		command_name = get_joined_name(temp);
		name = get_result(command_name, temp);
	}

	free(command_name);
	free_split(result);
	free_split(temp);
	return (name);
}
