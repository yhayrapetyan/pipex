#include "pipex.h"

static char	*get_joined_name(char **arr)
{
	char	*result;
	char	*temp;
	int		i;

	i = 0;
	result = NULL;
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

char	*rm_bslash(char *command_name)
{
	int	i;

	i = 0;
	while (command_name[i])
	{
		if (command_name[i] == '\\')
			command_name[i] = ' ';
		i++;
	}
	return (command_name);
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
		return (NULL);
	result[len - i] = NULL;
	while (len-- - i > 1)
	{
		result[len - i] = ft_strdup(arr[len]);
		if (result[len - i] == NULL)
		{
			free_split(result);
			return (NULL);
		}
	}
	command_name = rm_bslash(command_name);
	result[0] = ft_strdup(command_name);
	return (result);
}

static int	is_quote(char ch)
{
	if (ch == '"' || ch == '\'')
		return (1);
	return (0);
}

char	*get_quotes_content(char *command)
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

int	get_bslash_count(char *quote)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (quote[i])
	{
		i++;
		if (quote[i] == '\\')
			continue ;
		count++;
	}
	return (count);
}

char	*remove_back_slash(char *quote)
{
	int		i;
	int		j;
	int		count;
	char	*res;

	count = get_bslash_count(quote);
	res = (char *)malloc(sizeof(char *) * (count + 1));
	if (!res)
		NULL;
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

Quotes	get_quotes_count(char *command)
{
	Quotes	quotes;
	int		i;

	quotes.single_q = 0;
	quotes.double_q = 0;
	i = 0;
	while (command[i])
	{
		if (command[i] == '"')
			quotes.double_q++;
		if (command[i] == '\'')
			quotes.single_q++;
		i++;
	}
	return (quotes);
}

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

char	*remove_quotes(char *command)
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

void	clean_and_exit(char **content, char ***temp, char ***result, char ***name)
{
	if (content != NULL)
		free(*content);
	if (temp != NULL)
		free_split(*temp);
	if (result != NULL)
		free_split(*result);
	if (name != NULL)
	ft_error("Allocation Error\n", 17);
}

void	clean_vars(char **content, char ***temp, char ***result, char ***name)
{
	if (content != NULL)
		free(*content);
	if (temp != NULL)
		free_split(*temp);
	if (result != NULL)
		free_split(*result);
	if (name != NULL)
		free_split(*name);
}

void	get_name2(Qvars *vars)
{
	int	i;

	i = 0;
	while (vars->result[i])
		i++;
	vars->name = (char **)malloc(sizeof(char *) * (i + 2));
	if (!vars->name)
		clean_and_exit(&vars->content, &vars->temp, &vars->result, NULL);
	vars->name[i + 1] = NULL;
	vars->name[i] = vars->content;
	free(vars->content);
	i--;
	while (i >= 0)
	{
		vars->name[i] = ft_strdup(vars->result[i]);
		if (!vars->name[i])
			clean_and_exit(&vars->content, &vars->temp, &vars->result, &vars->name);
		i--;
	}
	clean_vars(&vars->content, &vars->temp, &vars->result, NULL);
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
	vars.name = get_result(vars.command_name, vars.temp);
	if (!vars.name)
		clean_and_exit(&vars.content, &vars.temp, NULL, NULL);
	clean_vars(&vars.content, &vars.temp, NULL, NULL);
	return (vars.name);
}

char	**get_name(char *command)
{
	Quotes	quotes_count;
	char	**name;

	quotes_count = get_quotes_count(command);
	if (quotes_count.single_q > 1 || quotes_count.double_q > 1)
		name = quotes_parse(command);
	else
		name = simple_parse(command);
//	int	i = 0;
//	while (name[i])
//	{
//		fprintf(stderr, "name[%d] = %s\n", i, name[i]);
//		i++;
//	}
	return (name);
}
